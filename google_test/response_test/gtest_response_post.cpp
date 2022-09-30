#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

// defined in gtest_response_error.cpp
std::string	GetHTMLPageSize(string const& html_file_path);
std::string	GetHTMLStringSize(char const* html_string);

// defined in gtest_response_expect.cpp
string GetFileContent(string const& file_path);

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");
static string message_body = GetFileContent("assets/hello.txt");

TEST(ResponsePostTest, PostExistingFile) {
	Connection connection(42, &config);

	string req_str = "POST /hello/public/hello.txt HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body;
	
	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 200);
	EXPECT_EQ(response.GetReasonPhrase(), "OK");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);
}

TEST(ResponsePostTest, PostNonExistantFile) {
	Connection connection(42, &config);

	string req_str = "POST /hello/upload/new3.txt HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body;
	
	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost/hello/upload/new3.txt");
	EXPECT_EQ(response.GetField("Content-Length"), "26");
	EXPECT_EQ(response.GetBodyStream()->gcount(), message_body.size());
}

TEST(ResponsePostTest, PostNonExistantEmptyFile) {
	Connection connection(42, &config);

	string req_str = "POST /hello/upload/new4.txt HTTP/1.1\r\nHost: localhost\nContent-Length: 0\n\n";
	
	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost/hello/upload/new4.txt");
	EXPECT_EQ(response.GetField("Content-Length"), "26");
	EXPECT_EQ(response.GetBodyStream()->gcount(), message_body.size());
}

TEST(ResponsePostTest, PostExistingFileNonExistantSubdir) {
	Connection connection(42, &config);

	string req_str = "POST /hello/nonexist/hello.txt HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body;
	
	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 403);
	EXPECT_EQ(response.GetReasonPhrase(), "Forbidden");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(403)));
}
