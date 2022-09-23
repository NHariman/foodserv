#include <gtest/gtest.h>
#include <fcntl.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");

TEST(ResponseExpectTest, IncompleteRequest) {
	Connection connection(42, &config);

	connection.Receive("POST /hello/upload/new.txt HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 100);
	EXPECT_EQ(response.GetReasonPhrase(), "Continue");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);

	int fd = open("assets/new.txt", O_RDONLY);
	if (fd < 0)
		cerr << "Unable to open new.txt\n";
	char buf[1082];
	int ret = read(fd, buf, 1082);
	if (ret < 0)
		cerr << "Unable to read from file\n";
	buf[ret] = '\0';
	string request_body = "Content-Length: " + to_string(strlen(buf)) + "\n\n" + buf;

	connection.Receive(request_body.c_str());
	Response	response2;
	response2 = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost/hello/upload/new.txt");
}

