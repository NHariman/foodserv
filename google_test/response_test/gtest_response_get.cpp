#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

// defined in gtest_response_error.cpp
std::string	GetHTMLPageSize(string const& html_file_path);
std::string	GetHTMLStringSize(char const* html_string);

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");

TEST(ResponseGetTest, GetExistingFile) {
	Connection connection(42, &config);

	connection.Receive("GET /hello.txt HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 200);
	EXPECT_EQ(response.GetReasonPhrase(), "OK");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLPageSize("assets/public/hello.txt"));
}

TEST(ResponseGetTest, GetNonExistantFile) {
	Connection connection(42, &config);

	connection.Receive("GET /nonexist.txt HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 404);
	EXPECT_EQ(response.GetReasonPhrase(), "Not Found");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(404)));
}
