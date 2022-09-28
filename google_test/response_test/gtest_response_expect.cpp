#include <gtest/gtest.h>
#include <fcntl.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");

static string GetFileContent(string const& file_path) {
	int fd = open(file_path.c_str(), O_RDONLY);
	if (fd < 0)
		cerr << "Unable to open new.txt\n";
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

	string req_str = "POST /hello/upload/new.txt HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\n";
	string message_body = GetFileContent("assets/new.txt");
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


	// connection.Receive(message_body.c_str());
	// Response	response2;
	// response2 = connection.DebugGetResponse();
	// EXPECT_EQ(response.GetStatusCode(), 201);
	// EXPECT_EQ(response.GetReasonPhrase(), "Created");
	// EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	// EXPECT_EQ(response.GetField("Connection"), "close");
	// EXPECT_EQ(response.GetField("Content-Type"), "text/plain");
	// EXPECT_EQ(response.GetField("Location"), "localhost/hello/upload/new.txt");
}

// TEST(ResponseExpectTest, ExpectWithNoMessage) {
// 	Connection connection(42, &config);

// 	string req_str = "POST /hello/upload/new.txt HTTP/1.1\r\nHost: localhost\nExpect: 100-continue\n\n";
// 	connection.Receive(req_str.c_str());
	
// 	Response const&	response = connection.DebugGetResponse();
// 	EXPECT_EQ(response.GetStatusCode(), 201);
// 	EXPECT_EQ(response.GetReasonPhrase(), "Created");
// 	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
// 	EXPECT_EQ(response.GetField("Connection"), "close");
// 	EXPECT_EQ(response.GetField("Content-Type"),"text/plain");
// 	EXPECT_EQ(response.GetField("Location"), "localhost/hello/upload/new.txt");
// }

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

