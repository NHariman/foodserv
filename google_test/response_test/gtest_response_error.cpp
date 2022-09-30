#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

#define CUSTOM_ERR_PATH "/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/assets/html/error/custom_error_test.html"

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");

// Helper function for getting HTML file length for comparison.
std::string	GetHTMLPageSize(string const& html_file_path) {
	std::ifstream file_stream(html_file_path);
	file_stream.seekg(0, std::ios_base::end); // move cursor to end of stream
	std::streampos	size = file_stream.tellg(); // get position of cursor
	file_stream.seekg(0); // restore cursor to beginning
	return std::to_string(size);
}

// Helper function for getting HTML string (i.e. default errors) length for comparison.
std::string	GetHTMLStringSize(char const* html_string) {
	size_t size = string(html_string).size();
	return std::to_string(size);
}

// 400 error test with invalid request target.
TEST(ResponseErrorTest, DefaultError400) {
	Connection connection(42, &config);

	connection.Receive("GET //thisisabadpath HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 400);
	EXPECT_EQ(response.GetReasonPhrase(), "Bad Request");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(400)));
}

// 405 error test with disallowed method and custom error_page set.
// Context:
// /dog location block only allows GET and POST, and sets custom page for 405.
TEST(ResponseErrorTest, CustomError405) {
	Connection connection(42, &config);

	connection.Receive("DELETE /dog HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 405);
	EXPECT_EQ(response.GetReasonPhrase(), "Method Not Allowed");
	EXPECT_EQ(response.GetField("Allow"), "GET, POST");
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLPageSize(CUSTOM_ERR_PATH));
}

// 405 error test with disallowed method.
// Context:
// /hello.txt location block only allows GET.
TEST(ResponseErrorTest, DefaultError405) {
	Connection connection(42, &config);

	connection.Receive("POST /hello.txt HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 405);
	EXPECT_EQ(response.GetReasonPhrase(), "Method Not Allowed");
	EXPECT_EQ(response.GetField("Allow"), "GET");
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(405)));
}

// 415 error test with Content-Encoding in request header.
TEST(ResponseErrorTest, DefaultError415) {
	Connection connection(42, &config);

	connection.Receive("GET /hello HTTP/1.1\r\nHost: localhost\nContent-Encoding: gzip\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 415);
	EXPECT_EQ(response.GetReasonPhrase(), "Unsupported Media Type");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(415)));
}

// 417 error test with value other than "100-continue" in Expect request header.
TEST(ResponseErrorTest, DefaultError417) {
	Connection connection(42, &config);

	connection.Receive("GET /hello HTTP/1.1\r\nHost: localhost\nExpect: 101-beep\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 417);
	EXPECT_EQ(response.GetReasonPhrase(), "Expectation Failed");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(417)));
}

// 501 error test with unrecognized method.
TEST(ResponseErrorTest, DefaultError501Method) {
	Connection connection(42, &config);

	connection.Receive("GET2 /hello HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 501);
	EXPECT_EQ(response.GetReasonPhrase(), "Not Implemented");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(501)));
}

// 501 error test with unrecognized transfer-encoding.
TEST(ResponseErrorTest, DefaultError501TE) {
	Connection connection(42, &config);

	connection.Receive("GET /hello HTTP/1.1\r\nHost: localhost\nTransfer-Encoding: compress\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 501);
	EXPECT_EQ(response.GetReasonPhrase(), "Not Implemented");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(501)));
}

// 505 error test with invalid HTTP version.
TEST(ResponseErrorTest, DefaultError505) {
	Connection connection(42, &config);

	connection.Receive("GET /hello HTTP/1.0\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 505);
	EXPECT_EQ(response.GetReasonPhrase(), "HTTP Version Not Supported");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(505)));
}

// test POST (should set Location, return 201)