#include <gtest/gtest.h>
#include <fcntl.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

// defined in gtest_response_post.cpp
std::streampos	GetFileContentCount(string const& file_path);

static NginxConfig config("../default.conf");
static string FILE_TO_SEND = "www/public/hello.txt";

string GetFileContent(string const& file_path) {
	int fd = open(file_path.c_str(), O_RDONLY);
	if (fd < 0)
		cerr << "Unable to open " << file_path << "\n";
	char buf[1082];
	int ret = read(fd, buf, 1082);
	if (ret < 0)
		cerr << "Unable to read from file\n";
	buf[ret] = '\0';
	close(fd);
	return string(buf);
}

TEST(ResponseExpectTest, ExpectWithMessageBody) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/hello2.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\n";
	string message_body = GetFileContent(FILE_TO_SEND);
	req_str += "Content-Length: " + to_string(message_body.size()) + "\n\n";

	connection.Receive(req_str.c_str());
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 100);
	EXPECT_EQ(response.GetReasonPhrase(), "Continue");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);

	// sending file
	connection.Receive(message_body.c_str());
	Response	response2;
	response2 = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost" + req_dir + req_target);
}

TEST(ResponseExpectTest, ExpectWithNoMessage) {
	Connection connection(42, &config);
	string req_dir = "/hello/";
	string alias_dir = "www/";
	string req_target = "upload/empty.txt";

	string req_str = "POST " + req_dir + req_target + " HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\n\n";
	connection.Receive(req_str.c_str());
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 201);
	EXPECT_EQ(response.GetReasonPhrase(), "Created");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"),"text/plain");
	EXPECT_EQ(response.GetField("Location"), "localhost" + req_dir + req_target);
	EXPECT_EQ(response.GetField("Content-Length"), "26");

	std::streampos count = GetFileContentCount(alias_dir + req_target);
	EXPECT_EQ(count, 0);
}

TEST(ResponseExpectTest, ExpectCompleteBadRequest) {
	Connection connection(42, &config);

	string req_str = "POST //hello/badpath HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\nTransfer-Encoding: chunked\n\n";
	connection.Receive(req_str.c_str());
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 400);
	EXPECT_EQ(response.GetReasonPhrase(), "Bad Request");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
}

TEST(ResponseExpectTest, ExpectIncompleteRequest) {
	Connection connection(42, &config);

	string req_str = "POST /hello/upload/beep.txt HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\nTransfer-Encoding: chunked\n\n";
	connection.Receive(req_str.c_str());
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 100);
	EXPECT_EQ(response.GetReasonPhrase(), "Continue");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);

	sleep(3);
	EXPECT_TRUE(connection.HasTimedOut(2));
}
