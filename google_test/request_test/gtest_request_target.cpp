#include <gtest/gtest.h>

#include "../../src/request/uri.hpp"
#include "../../src/request/request_target_parser.hpp"
#include "../../src/err/exception.hpp"

TEST(RequestTargetTest, ParsePathSimple) {
	URI	request_uri("/contact_form.php");
	EXPECT_EQ(request_uri.GetParsedURI(), "/contact_form.php");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/contact_form.php");
	EXPECT_TRUE(request_uri.GetQuery().empty());
}

TEST(RequestTargetTest, ParseQuerySimple) {
	URI	request_uri("/where?q=now");
	EXPECT_EQ(request_uri.GetParsedURI(), "/where?q=now");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/where");
	EXPECT_EQ(request_uri.GetQuery(), "q=now");
	request_uri = "/where?q=nowwithhash#";
	EXPECT_EQ(request_uri.GetParsedURI(), "/where?q=nowwithhash");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/where");
	EXPECT_EQ(request_uri.GetQuery(), "q=nowwithhash");
}

TEST(RequestTargetTest, ParsePathMultiSlash) {
	URI	request_uri("/path/to/resource");
	EXPECT_EQ(request_uri.GetParsedURI(), "/path/to/resource");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/path/to/resource");
	EXPECT_TRUE(request_uri.GetQuery().empty());
}

TEST(RequestTargetTest, ParsePathMultiQueryMulti) {
	URI	request_uri("/path/to/query?param1=value&param2=value2");
	EXPECT_EQ(request_uri.GetParsedURI(), "/path/to/query?param1=value&param2=value2");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/path/to/query");
	EXPECT_EQ(request_uri.GetQuery(), "param1=value&param2=value2");
	request_uri = "/path/to/query?new=/google.com";
	EXPECT_EQ(request_uri.GetParsedURI(), "/path/to/query?new=/google.com");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/path/to/query");
	EXPECT_EQ(request_uri.GetQuery(), "new=/google.com");
}

TEST(RequestTargetTest, ParsePercentEncoded) {
	URI	request_uri("/where%20/are%7E/we?q=now?text=Hello+G%C3%BCnter");
	EXPECT_EQ(request_uri.GetParsedURI(), "/where /are~/we?q=now?text=Hello+Günter");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/where /are~/we");
	EXPECT_EQ(request_uri.GetQuery(), "q=now?text=Hello+Günter");
	request_uri ="/where/are%7e/we?q=now"; // lowercase hexdigit to test normalization
	EXPECT_EQ(request_uri.GetParsedURI(), "/where/are~/we?q=now");
	EXPECT_TRUE(request_uri.GetHost().empty());
	EXPECT_EQ(request_uri.GetPath(), "/where/are~/we");
	EXPECT_EQ(request_uri.GetQuery(), "q=now");
}

TEST(RequestTargetTest, InvalidPathStart) {
	URI uri;
	RequestTargetParser parser1, parser2;

	EXPECT_THROW({
		URI	request_uri("//thisisabadpath");
	}, BadRequestException);
	EXPECT_THROW({
		parser1.Parse(uri, "%25anotherbadpath");
	}, BadRequestException);
	EXPECT_THROW({
		parser2.Parse(uri, "yetanotherbadpath");
	}, BadRequestException);
}

TEST(RequestTargetTest, InvalidPathMiddle) {
	EXPECT_THROW({
		URI	request_uri("/path#/to");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path^to");
	}, BadRequestException);
}

TEST(RequestTargetTest, InvalidPercent) {
	EXPECT_THROW({
		URI	request_uri("/path%2=to");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path%$3to");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path/to?q%2==1");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path/to?q=1%*1");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/where/are%7e/we#?q=now");
	}, BadRequestException);
}

TEST(RequestTargetTest, InvalidQuery) {
	EXPECT_THROW({
		URI	request_uri("/path/to?q^=1");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path/to?q=1^");
	}, BadRequestException);
	EXPECT_THROW({
		URI	request_uri("/path/to?q=1#bad");
	}, BadRequestException);
}
