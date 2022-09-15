#include <gtest/gtest.h>

#include "../request.hpp"
#include "../../err/exception.hpp"

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/src/request/testing/default.conf");

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
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET  /hello.txt HTTP/1.1\nHost: localhost\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt  HTTP/1.1\nHost: localhost\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1 \nHost: localhost\n\n");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidDelimiter) {
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt\tHTTP/1.1\nHost: localhost\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\n\rHost: localhost\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\t\nHost: localhost\n\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.1\r\tHost: localhost\n\n");
	}, BadRequestException);
}

TEST(RequestLineTest, InvalidMethodHTTPVer) {
	EXPECT_THROW({
		Request request(&config);
		request.Parse("CONNECT /hello.txt HTTP/1.1\nHost: localhost\n\n");
	}, NotImplementedException);
	EXPECT_THROW({
		Request request(&config);
		request.Parse("GET /hello.txt HTTP/1.0\nHost: localhost\n\n");
	}, HTTPVersionNotSupportedException);
}