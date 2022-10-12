#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"
#include <fstream>

using namespace std;

// defined in gtest_response_error.cpp
std::string	GetHTMLStringSize(char const* html_string);

static NginxConfig config("../default.conf");

TEST(ResponseDeleteTest, DeleteExistantFile) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string req_target = "upload/delete_me.txt";

	string req_str = "DELETE " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n\n";

	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 200);
	EXPECT_EQ(response.GetReasonPhrase(), "OK");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), "26"); // File successfully deleted
}

TEST(ResponseDeleteTest, DeleteNonExistantFile) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string req_target = "upload/nonexistant.txt";

	string req_str = "DELETE " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n\n";

	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 404);
	EXPECT_EQ(response.GetReasonPhrase(), "Not Found");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(404)));
}

TEST(ResponseDeleteTest, DeleteNonExistantDir) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string req_target = "nonexistant/existing.txt";

	string req_str = "DELETE " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\n\n";

	connection.Receive(req_str.c_str());
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 404);
	EXPECT_EQ(response.GetReasonPhrase(), "Not Found");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), GetHTMLStringSize(GetServerErrorPage(404)));
}

TEST(ResponseDeleteTest, DeleteSubdirDirectory) {
	Connection connection(42, &config);

	string req_str = "DELETE /hello/ HTTP/1.1\r\nHost: localhost\n\n";

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
