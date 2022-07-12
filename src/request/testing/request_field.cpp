#include <gtest/gtest.h>

#include "../request_parser.hpp"
#include "../exception.hpp"

TEST(RequestHeaderTest, ParseSingleField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nHost: www.example.com\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
}

TEST(RequestHeaderTest, ParseMultiField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3\nHost: www.example.com\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
	EXPECT_EQ(parser.GetHeaderFieldValue("user-agent"), "curl/7.16.3");
}

TEST(RequestHeaderTest, ParseMultiValueField) {
	RequestParser parser;

	parser.Parse("GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.16.3 libcurl/7.16.3\nHost: www.example.com\nAccept-Language: en, mi\n\n");
	EXPECT_EQ(parser.GetHeaderFieldValue("host"), "www.example.com");
	EXPECT_EQ(parser.GetHeaderFieldValue("user-agent"), "curl/7.16.3 libcurl/7.16.3");
	EXPECT_EQ(parser.GetHeaderFieldValue("Accept-Language"), "en, mi");
}