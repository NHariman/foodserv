#include <gtest/gtest.h>

#include "../uri.hpp"
#include "../uri_host_parser.hpp"
#include "../exception.hpp"

TEST(URIHostTest, ParseHostRegName) {
	URIHostParser	parser;
	string			parsed_host;

	parser.Parse(parsed_host, "localhost");
	EXPECT_EQ(parsed_host, "localhost");

	parser.Parse(parsed_host, "localhost:80"); // with port
	EXPECT_EQ(parsed_host, "localhost:80");
	
	parser.Parse(parsed_host, "www.ex%C3%BCmple.com"); // with percent-encoding
	EXPECT_EQ(parsed_host, "www.exümple.com");

	parser.Parse(parsed_host, "www.example.hello.com");
	EXPECT_EQ(parsed_host, "www.example.hello.com");
}

TEST(URIHostTest, ParseHostIPv4) {
	URI	uri("127.0.0.1");
	EXPECT_EQ(uri.GetHost(), "127.0.0.1");

	uri = "127.0.0.1:3000";
	EXPECT_EQ(uri.GetHost(), "127.0.0.1:3000"); // with port
}

TEST(URIHostTest, ParseHostIPv6) {
	URI	uri("[2001:db8:85a3:8d3:1319:8a2e:370:7348]");
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]");

	uri = "[2001:db8::8d3:1319:8a2e:370:7348]"; // elided zeroes
	EXPECT_EQ(uri.GetHost(), "[2001:db8::8d3:1319:8a2e:370:7348]");

	uri = "[2001:db8:85A3:8d3:1319:8a2e:370:7348]"; // uppercase hexadecimal
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]");

	uri = "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:443"; // with port
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:443");

	uri = "[2001:db8:85a3:8d3:1319:8a2e:127.0.0.1]"; // with IPv4 ending
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:127.0.0.1]");

	uri = "[::1]";
	EXPECT_EQ(uri.GetHost(), "[::1]"); // 0:0:0:0:0:0:0:1 elided

	uri = "[::]";
	EXPECT_EQ(uri.GetHost(), "[::]"); // 0:0:0:0:0:0:0:0 elided
}

TEST(URIHostTest, InvalidRegName) {
	EXPECT_THROW({
		URI	uri("www.example#.com");
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("www.ex@mple.com");
	}, BadRequestException);
}

TEST(URIHostTest, InvalidIPv4) {
	EXPECT_THROW({
		URI	uri("127.0.0"); // too little elements
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("127.0.0:443"); // too little elements
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("127.0.0.1.1"); // too many elements
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("127.0.0.1:8P000"); // non-digit in port
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("127.0.0.500"); // element exceeds limit (0-255)
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("127.0.0.-500"); // element below limit (0-255)
	}, BadRequestException);
}

TEST(URIHostTest, InvalidIPv6) {
	EXPECT_THROW({
		URI	uri("2001:db8:85a3:8d3:1319:8a2e:370:7348"); // missing brackets
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("[2001:db8:85a3:8d3:1319:8a2e:370:7348"); // missing closing bracket
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("2001:db8:85a3:8d3:1319:8a2e:370:7348]"); // missing opening bracket
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("[2001:db8:85a3:8d3:1319:::370:7348]"); // more than 2 :
	}, BadRequestException);
	EXPECT_THROW({
		URI	uri("[2001:db8:85a3:8d3:13190::370:7348]"); // too many digits in element
	}, BadRequestException);
}