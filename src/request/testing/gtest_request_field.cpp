#include <gtest/gtest.h>

#include "../request.hpp"
#include "../exception.hpp"

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/config_files/default.conf");

TEST(RequestFieldParserTest, ParseSingleField) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\n");
	EXPECT_EQ(request.GetField("host"), "www.example.com");
}

TEST(RequestFieldParserTest, ParseMultiField) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\r\nHost: www.example.com\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");
	EXPECT_EQ(request1.GetField("user-agent"), "curl/7.16.3");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl  \r\nHost:   www.example.com\n\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");
	EXPECT_EQ(request2.GetField("user-agent"), "curl/7.16.3 libcurl");
}

TEST(RequestFieldParserTest, ParseMultiValueField) {
	Request request(&config);
	request.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: www.example.com\r\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(request.GetField("host"), "www.example.com");
	EXPECT_EQ(request.GetField("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(request.GetField("Accept-Language"), "en, mi");
}

TEST(RequestFieldParserTest, ParseCRLF) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");

	Request request3(&config);
	request3.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\r\n");
	EXPECT_EQ(request3.GetField("host"), "www.example.com");
}

TEST(RequestFieldParserTest, ParseFieldwithOWS) {
	Request request1(&config);
	request1.Parse("GET /hello.txt HTTP/1.1\r\nHost:  www.example.com\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");

	Request request2(&config);
	request2.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.com  \n\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");
}

TEST(RequestFieldParserTest, InvalidFields) {
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.c\vom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.\fcom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\nHo st: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\nHost : www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.com\v\n\n");
	}, BadRequestException);
}
