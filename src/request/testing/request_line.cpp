#include <gtest/gtest.h>

#include "../request_parser.hpp"
#include "../exception.hpp"

TEST(RequestLineTest, ParseGet) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.com");
	EXPECT_EQ(parser.GetMethod(), "GET");
	EXPECT_EQ(parser.GetTarget(), "/hello.txt");
	EXPECT_EQ(parser.GetVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, ParseGetCRLF) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\r\nHost: www.example.com");
	EXPECT_EQ(parser.GetMethod(), "GET");
	EXPECT_EQ(parser.GetTarget(), "/hello.txt");
	EXPECT_EQ(parser.GetVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, InvalidSpaces) {
	EXPECT_THROW({
		RequestParser parser("GET  /hello.txt HTTP/1.1\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt  HTTP/1.1\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1 \nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser(" GET /hello.txt HTTP/1.1 \nHost: www.example.com");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidDelimiter) {
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt\tHTTP/1.1\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\n\rHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\t\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.1\r\tHost: www.example.com");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidMethodHTTPVer) {
	EXPECT_THROW({
		RequestParser parser("CONNECT /hello.txt HTTP/1.1\nHost: www.example.com");
	}, NotImplementedException);
	EXPECT_THROW({
		RequestParser parser("GET /hello.txt HTTP/1.0\nHost: www.example.com");
	}, HTTPVersionNotSupportedException);
}