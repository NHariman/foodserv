#include <gtest/gtest.h>

// #include "../request_parser.hpp"
#include "../request_parser0.hpp"
#include "../exception.hpp"

TEST(RequestLineTest, ParseGet) {
	RequestParser parser;

	parser.ParseRequest("GET /hello.txt HTTP/1.1\nHost: www.example.com");
	EXPECT_EQ(parser.GetMethod(), "GET");
	EXPECT_EQ(parser.GetTarget(), "/hello.txt");
	EXPECT_EQ(parser.GetVersion(), "1.1");
}

TEST(RequestLineTest, InvalidSpaces) {
	RequestParser parser;
	EXPECT_THROW({
		parser.ParseRequest("GET  /hello.txt HTTP/1.1\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		parser.ParseRequest("GET /hello.txt  HTTP/1.1\nHost: www.example.com");
	}, BadRequestException);
	EXPECT_THROW({
		parser.ParseRequest("GET /hello.txt HTTP/1.1 \nHost: www.example.com");
	}, BadRequestException);
}