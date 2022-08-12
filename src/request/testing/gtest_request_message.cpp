#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../request.hpp"

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: www.example.com\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config(NULL);

// Helper function used to construct Request objects with passed string
// containing request message. Returns parsed message.
static string	ConstructAndGetMessage(string const& rest_of_header) {
	string req_str = POST_Req + rest_of_header;
	Request request(&config, req_str.c_str());
	return request.GetMessageBody();
}

TEST(RequestMessageTest, ValidMessageNormal) {
	string message;

	message = ConstructAndGetMessage("Content-Length: 12\r\n\nHello World!");
	EXPECT_EQ(message, "Hello World!");

	message = ConstructAndGetMessage("Content-Length: 17\r\n\nHello World!\nBye!");
	EXPECT_EQ(message, "Hello World!\nBye!");

	message = ConstructAndGetMessage("Content-Length: 19\r\n\nHello World!\nBye!\r\n");
	EXPECT_EQ(message, "Hello World!\nBye!\r\n");
}

TEST(RequestMessageTest, ValidMessageChunked) {
	string message;

	message = ConstructAndGetMessage(CHUNKED +
		"4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
	EXPECT_EQ(message, "Wikipedia in \r\n\r\nchunks.");

	message = ConstructAndGetMessage(CHUNKED + "0\r\n");
	EXPECT_EQ(message, "");
}

TEST(RequestMessageTest, ValidMessageChunkedTrailers) {
	string req = POST_Req + CHUNKED +
		"7\nChunks.\r\n0\r\nPrefer: return=representation\r\n\r\n";
	Request request(&config, req.c_str());
	EXPECT_EQ(request.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request.GetField("Prefer"), "return=representation");
}

TEST(RequestMessageTest, InvalidMessageChunked) {
	string req_str;

	EXPECT_THROW({
		req_str = POST_Req + CHUNKED + "0\r\r\n";
		Request request(&config, req_str.c_str());
	}, BadRequestException);
}

TEST(RequestMessageTest, InvalidChunkedTrailers) {
	string req_str;

	EXPECT_THROW({
		req_str = POST_Req + CHUNKED + "0\r\nDate: today\r\n\r\n";
		Request request(&config, req_str.c_str());
	}, BadRequestException);
}