#include <gtest/gtest.h>

#include "../request.hpp"
#include "../exception.hpp"

static NginxConfig config(NULL);

TEST(RequestLineTest, ParseGet) {
	Request request(&config, "GET /hello.txt HTTP/1.1\nHost: www.example.com\r\n\n");
	EXPECT_EQ(request.GetMethod(), "GET");
	EXPECT_EQ(request.GetTarget(), "/hello.txt");
	EXPECT_EQ(request.GetVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, ParseGetCRLF) {
	Request request(&config, "GET /hello.txt HTTP/1.1\r\nHost: www.example.com\n\n");
	EXPECT_EQ(request.GetMethod(), "GET");
	EXPECT_EQ(request.GetTarget(), "/hello.txt");
	EXPECT_EQ(request.GetVersion(), "HTTP/1.1");
}

TEST(RequestLineTest, InvalidSpaces) {
	EXPECT_THROW({
		Request request(&config, "GET  /hello.txt HTTP/1.1\nHost: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt  HTTP/1.1\nHost: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt HTTP/1.1 \nHost: www.example.com\n\n");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidDelimiter) {
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt\tHTTP/1.1\nHost: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt HTTP/1.1\n\rHost: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt HTTP/1.1\t\nHost: www.example.com\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt HTTP/1.1\r\tHost: www.example.com\n\n");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidMethodHTTPVer) {
	EXPECT_THROW({
		Request request(&config, "CONNECT /hello.txt HTTP/1.1\nHost: www.example.com\n\n");
	}, NotImplementedException);
	EXPECT_THROW({
		Request request(&config, "GET /hello.txt HTTP/1.0\nHost: www.example.com\n\n");
	}, HTTPVersionNotSupportedException);
}