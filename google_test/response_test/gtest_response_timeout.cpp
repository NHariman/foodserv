#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"
#include <fstream>

using namespace std;

// defined in gtest_response_error.cpp
std::string	GetHTMLPageSize(string const& html_file_path);
std::string	GetHTMLStringSize(char const* html_string);

// defined in gtest_response_expect.cpp
string GetFileContent(string const& file_path);

// defined in gtest_response_post.cpp
std::streampos	GetFileContentCount(string const& file_path);

static NginxConfig config("../default.conf");
static string FILE_TO_SEND = "www/public/hello.txt";

// Only sends half of payload body and tests if timeout is detected
TEST(ResponseTimeoutTest, IncompleteRequestWithCL) {
	Connection connection(42, &config);
	string message_body = GetFileContent(FILE_TO_SEND);
	string req_dir = "/hello/";
	string req_target = "upload/hello4.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body.substr(0, message_body.size() / 2);

	connection.Receive(req_str.c_str());

	sleep(2);
	EXPECT_FALSE(connection.HasTimedOut(3));
	sleep(2);
	EXPECT_TRUE(connection.HasTimedOut(3));

	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 408);
	EXPECT_EQ(response.GetReasonPhrase(), "Request Timeout");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(408)));
}

// chunked-encoded request without last CRLF chunk
TEST(ResponseTimeoutTest, IncompleteRequestChunkedEncoded) {
	Connection connection(42, &config);

	string req_dir = "/hello/";
	string req_target = "upload/hello5.txt";
	
	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
	req_str += "Transfer-Encoding: chunked\n\n";
	req_str += "4\r\nBye!\r\n0\r\n";
	connection.Receive(req_str.c_str());

	sleep(4);
	EXPECT_TRUE(connection.HasTimedOut(3));

	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 408);
	EXPECT_EQ(response.GetReasonPhrase(), "Request Timeout");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(408)));
}

// Checks if timer is correctly reset after more of request is received.
TEST(ResponseTimeoutTest, CompleteRequestChunked) {
	Connection connection(42, &config);
	string message_body = GetFileContent(FILE_TO_SEND);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/hello6.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body.substr(0, message_body.size() / 2);
	connection.Receive(req_str.c_str());

	sleep(2);
	EXPECT_FALSE(connection.HasTimedOut(3));
	req_str = message_body.substr(message_body.size() / 2);
	connection.Receive(req_str.c_str());
	sleep(2);
	EXPECT_FALSE(connection.HasTimedOut(3));

	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost" + req_dir + req_target);
	EXPECT_EQ(response.GetField("Content-Length"), "26"); // File successfully created

	std::streampos count = GetFileContentCount(alias_dir + req_target);
	EXPECT_EQ(count, message_body.size());
}
