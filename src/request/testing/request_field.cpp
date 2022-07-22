#include <gtest/gtest.h>

#include "../request_parser.hpp"
#include "../exception.hpp"

TEST(RequestHeaderTest, ParseSingleField) {
	RequestParser parser1("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\n");
	EXPECT_EQ(parser1.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseMultiField) {
	RequestParser parser1("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\r\nHost: www.example.com\n\n");
	EXPECT_EQ(parser1.GetField("host"), "www.example.com");
	EXPECT_EQ(parser1.GetField("user-agent"), "curl/7.16.3");

	RequestParser parser2("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl  \r\nHost:   www.example.com\n\n");
	EXPECT_EQ(parser2.GetField("host"), "www.example.com");
	EXPECT_EQ(parser2.GetField("user-agent"), "curl/7.16.3 libcurl");
}

TEST(RequestHeaderTest, ParseMultiValueField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: www.example.com\r\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(parser.GetField("host"), "www.example.com");
	EXPECT_EQ(parser.GetField("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(parser.GetField("Accept-Language"), "en, mi");
}

TEST(RequestHeaderTest, ParseCRLF) {
	RequestParser parser1("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\n");
	EXPECT_EQ(parser1.GetField("host"), "www.example.com");

	RequestParser parser2("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n\r\n");
	EXPECT_EQ(parser2.GetField("host"), "www.example.com");

	RequestParser parser3("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\r\n");
	EXPECT_EQ(parser3.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseFieldwithOWS) {
	RequestParser parser1("GET /hello.txt HTTP/1.1\r\nHost:  www.example.com\n\n");
	EXPECT_EQ(parser1.GetField("host"), "www.example.com");

	RequestParser parser2("GET /hello.txt HTTP/1.1\nHost: www.example.com  \n\n");
	EXPECT_EQ(parser2.GetField("host"), "www.example.com");
}

TEST(RequestHeaderTest, InvalidFields) {
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.c\vom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.\fcom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHo st: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost : www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.com\v\n\n");
	}, BadRequestException);
}
