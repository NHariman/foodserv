#include <gtest/gtest.h>

#include "../uri.hpp"
#include "../uri_host_parser.hpp"
#include "../exception.hpp"

TEST(URIHostTest, ParseHostRegName) {
	URIHostParser	parser;
	string			parsed_host;

	parser.Parse(parsed_host, "www.example.com");
	EXPECT_EQ(parsed_host, "www.example.com");

	parser.Parse(parsed_host, "www.example.com:80");
	EXPECT_EQ(parsed_host, "www.example.com:80");
}

TEST(URIHostTest, ParseHostIPv4) {
	URI	uri("127.0.0.1");
	EXPECT_EQ(uri.GetHost(), "127.0.0.1");

	uri = "127.0.0.1:3000";
	EXPECT_EQ(uri.GetHost(), "127.0.0.1:3000");
}

TEST(URIHostTest, ParseHostIPv6) {
	URI	uri("[2001:db8:85a3:8d3:1319:8a2e:370:7348]");
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]");

	uri = "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:443";
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:370:7348]:443");

	uri = "[2001:db8:85a3:8d3:1319:8a2e:127.0.0.1]";
	EXPECT_EQ(uri.GetHost(), "[2001:db8:85a3:8d3:1319:8a2e:127.0.0.1]");

	uri = "::1";
	EXPECT_EQ(uri.GetHost(), "::1");

	uri = "::";
	EXPECT_EQ(uri.GetHost(), "::");
}