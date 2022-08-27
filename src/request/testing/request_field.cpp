#include <gtest/gtest.h>

#include "../request.hpp"
#include "../exception.hpp"

TEST(RequestHeaderTest, ParseSingleField) {
	Request request("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\n");
	EXPECT_EQ(request.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseMultiField) {
	Request request1("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\r\nHost: www.example.com\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");
	EXPECT_EQ(request1.GetField("user-agent"), "curl/7.16.3");

	Request request2("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl  \r\nHost:   www.example.com\n\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");
	EXPECT_EQ(request2.GetField("user-agent"), "curl/7.16.3 libcurl");
}

TEST(RequestHeaderTest, ParseMultiValueField) {
	Request request("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: www.example.com\r\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(request.GetField("host"), "www.example.com");
	EXPECT_EQ(request.GetField("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(request.GetField("Accept-Language"), "en, mi");
}

TEST(RequestHeaderTest, ParseCRLF) {
	Request request1("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");

	Request request2("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");

	Request request3("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\r\n");
	EXPECT_EQ(request3.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseFieldwithOWS) {
	Request request1("GET /hello.txt HTTP/1.1\r\nHost:  www.example.com\n\n");
	EXPECT_EQ(request1.GetField("host"), "www.example.com");

	Request request2("GET /hello.txt HTTP/1.1\nHost: www.example.com  \n\n");
	EXPECT_EQ(request2.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, InvalidFields) {
	EXPECT_THROW({
		Request request("GET /hello.txt HTTP/1.1\nHost: www.example.c\vom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request("GET /hello.txt HTTP/1.1\nHost: www.example.\fcom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request("GET /hello.txt HTTP/1.1\nHo st: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request("GET /hello.txt HTTP/1.1\nHost : www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request("GET /hello.txt HTTP/1.1\nHost: www.example.com\v\n\n");
	}, BadRequestException);
}
