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

static NginxConfig config("../default.conf");
static string FILE_TO_SEND = "www/public/hello.txt";

std::streampos	GetFileContentCount(string const& file_path) {
	ifstream file(file_path);
	file.seekg(0, std::ios_base::end); // move cursor to end of stream
	std::streampos	size = file.tellg(); // get position of cursor
	file.seekg(0); // restore cursor to beginning
	return size;
}

TEST(ResponsePostTest, PostExistingFile) {
	Connection connection(42, &config);
	string message_body = GetFileContent(FILE_TO_SEND);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/existing.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
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

	std::streampos count = GetFileContentCount(alias_dir + req_target);
	EXPECT_GT(count, 0);
}

TEST(ResponsePostTest, PostNonExistantFile) {
	Connection connection(42, &config);
	string message_body = GetFileContent(FILE_TO_SEND);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/hello3.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";
	req_str += message_body;

	connection.Receive(req_str.c_str());
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

TEST(ResponsePostTest, PostNonExistantEmptyFile) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/empty2.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n";
	req_str += "Content-Length: 0\n\n";
	
	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost" + req_dir + req_target);
	EXPECT_EQ(response.GetField("Content-Length"), "26");

	std::streampos count = GetFileContentCount(alias_dir + req_target);
	EXPECT_EQ(count, 0);
}

TEST(ResponsePostTest, PostExistingFileNonExistantSubdir) {
	Connection connection(42, &config);
	string message_body = GetFileContent(FILE_TO_SEND);
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
