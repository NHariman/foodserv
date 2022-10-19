#include <gtest/gtest.h>

#include "../../src/request/request.hpp"
#include "../../src/err/exception.hpp"

using namespace std;

// defined in gtest_request_message.cpp
int	ConstructAndGetStatus(std::string const& req_str);

static NginxConfig config("../default.conf");

TEST(RequestLineTest, ParseGet) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\nHost: localhost\r\n\n");
	EXPECT_EQ(request.GetMethod(), "GET");
	EXPECT_EQ(request.GetTargetString(), "localhost/hello.txt");
	EXPECT_EQ(request.GetHTTPVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, ParseGetCRLF) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\r\nHost: localhost\n\n");
	EXPECT_EQ(request.GetMethod(), "GET");
	EXPECT_EQ(request.GetTargetString(), "localhost/hello.txt");
	EXPECT_EQ(request.GetHTTPVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, InvalidSpaces) {
	string req_str = "GET  /hello.txt HTTP/1.1\nHost: localhost\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	req_str = "GET /hello.txt  HTTP/1.1\nHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1 \nHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

}

TEST(RequestLineTest, InvalidDelimiter) {
	string req_str = "GET /hello.txt\tHTTP/1.1\nHost: localhost\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1\n\rHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1\t\nHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1\r\tHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

}

TEST(RequestLineTest, InvalidMethodHTTPVer) {
	string req_str = "CONNECT /hello.txt HTTP/1.1\nHost: localhost\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 501); // Not Implemented error
	
	req_str = "GET /hello.txt HTTP/1.0\nHost: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 505); // HTTP Version Not Supported error
}