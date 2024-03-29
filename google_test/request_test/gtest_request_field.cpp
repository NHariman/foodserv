#include <gtest/gtest.h>

#include "../../src/request/request.hpp"
#include "../../src/err/exception.hpp"

using namespace std;

// defined in gtest_request_message.cpp
int	ConstructAndGetStatus(std::string const& req_str);

static NginxConfig config("../default.conf");


TEST(RequestFieldParserTest, ParseSingleField) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\r\nHost: localhost\n\n");
	EXPECT_EQ(request.GetField("host"), "localhost");
}

TEST(RequestFieldParserTest, ParseMultiField) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\r\nHost: localhost\n\n");
	EXPECT_EQ(request1.GetField("host"), "localhost");
	EXPECT_EQ(request1.GetField("user-agent"), "curl/7.16.3");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl  \r\nHost:   localhost\n\n");
	EXPECT_EQ(request2.GetField("host"), "localhost");
	EXPECT_EQ(request2.GetField("user-agent"), "curl/7.16.3 libcurl");
}

TEST(RequestFieldParserTest, ParseMultiValueField) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: localhost\r\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(request.GetField("host"), "localhost");
	EXPECT_EQ(request.GetField("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(request.GetField("Accept-Language"), "en, mi");
}

TEST(RequestFieldParserTest, ParseCRLF) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\r\nHost: localhost\r\n\n");
	EXPECT_EQ(request1.GetField("host"), "localhost");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\r\nHost: localhost\r\n\r\n");
	EXPECT_EQ(request2.GetField("host"), "localhost");

	Request request3(&config);
	request3.Parse("GET /hello.txt HTTP/1.1\r\nHost: localhost\n\r\n");
	EXPECT_EQ(request3.GetField("host"), "localhost");
}

TEST(RequestFieldParserTest, ParseFieldwithOWS) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\r\nHost:  localhost\n\n");
	EXPECT_EQ(request1.GetField("host"), "localhost");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\nHost: localhost  \n\n");
	EXPECT_EQ(request2.GetField("host"), "localhost");
}

TEST(RequestFieldParserTest, InvalidFields) {
	string req_str = "GET /hello.txt HTTP/1.1\nHost: www.example.c\vom\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1\nHost: www.example.\fcom\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	req_str = "GET /hello.txt HTTP/1.1\nHo st: localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = "GET /hello.txt HTTP/1.1\nHost : localhost\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	req_str = "GET /hello.txt HTTP/1.1\nHost: localhost\v\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
}

TEST(RequestFieldParserTest, InvalidFieldSize) {
	string long_str(8193, 'a');

	string	req_str = "GET /hello.txt HTTP/1.1\nH" + long_str + ": www.example.com\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 431); // Request Header Fields Too Large error

	req_str = "GET /hello.txt HTTP/1.1\nHost:" + long_str + "\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 431); // Request Header Fields Too Large error
}
