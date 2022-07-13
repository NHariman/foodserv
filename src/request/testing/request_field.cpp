#include <gtest/gtest.h>

#include "../request_parser.hpp"
#include "../exception.hpp"

TEST(RequestHeaderTest, ParseSingleField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseMultiField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\r\nHost: www.example.com\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
	EXPECT_EQ(parser.GetHeaderFieldValue("user-agent"), "curl/7.16.3");
}

TEST(RequestHeaderTest, ParseMultiValueField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: www.example.com\r\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
	EXPECT_EQ(parser.GetHeaderFieldValue("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(parser.GetHeaderFieldValue("Accept-Language"), "en, mi");
}

TEST(RequestHeaderTest, ParseFieldwithOWS) {
	RequestParser parser1("GET /hello.txt HTTP/1.1\r\nHost:  www.example.com\n\n");
	EXPECT_EQ(parser1.GetHeaderFieldValue("host"), "www.example.com");

	RequestParser parser2("GET /hello.txt HTTP/1.1\nHost: www.example.com  \n\n");
	EXPECT_EQ(parser2.GetHeaderFieldValue("host"), "www.example.com");
}

TEST(RequestHeaderTest, InvalidFields) {
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.c om\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.\tcom\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\nHo st: www.example.com\n\n");
	}, BadRequestException);
}
