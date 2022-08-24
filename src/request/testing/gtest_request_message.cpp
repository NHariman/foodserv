#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../request.hpp"

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/config_files/default.conf");

// Helper function used to construct Request objects with passed string
// containing request message. Returns parsed message.
static string	ConstructAndGetMessage(string const& rest_of_header) {
	string req_str = POST_Req + rest_of_header;
	Request request(&config);
	request.Parse(req_str.c_str());
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

	message = ConstructAndGetMessage(CHUNKED + "0\r\n\r\n");
	EXPECT_EQ(message, "");
}

// TEST(RequestMessageTest, ValidMessageChunkedMulti) {
// 	string chunk1 = "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
// 	string req_str = POST_Req + message;
// 	Request request(&config);
	// request.Parse(req_str.c_str());

// 	message = ConstructAndGetMessage(CHUNKED +
// 		"4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
// 	EXPECT_EQ(message, "Wikipedia in \r\n\r\nchunks.");
// }

TEST(RequestMessageTest, ValidMessageChunkedTrailers) {
	string req = POST_Req + CHUNKED +
		"7\nChunks.\r\n0\r\nPrefer: return=representation\r\n\r\n";
	Request request1(&config);
	request1.Parse(req.c_str());
	EXPECT_EQ(request1.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request1.GetField("Prefer"), "return=representation");

	req = POST_Req + CHUNKED +
		"7\nChunks.\r\n0\r\nPrefer: return=representation\r\nAccept: text/html\n\r\n";
	Request request2(&config);
	request2.Parse(req.c_str());
	EXPECT_EQ(request2.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request2.GetField("Prefer"), "return=representation");
	EXPECT_EQ(request2.GetField("Accept"), "text/html");
}

TEST(RequestMessageTest, ValidMessageChunkedExt) {
	string message;

	message = ConstructAndGetMessage(CHUNKED +
		"4;ext1=true;ext2\r\nBye!\r\n0\r\n\r\n");
	EXPECT_EQ(message, "Bye!");

	message = ConstructAndGetMessage(CHUNKED +
		"4\r\nBye!\r\n0;ext1=true;ext2\r\n\r\n");
	EXPECT_EQ(message, "Bye!");
}

TEST(RequestMessageTest, InvalidMessageChunked) {
	// invalid line ending
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "0\r\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// missing last chunk
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "4\r\nBye!\r\n\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// missing last CRLF
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "4\r\nBye!\r\n0\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "0\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}

TEST(RequestMessageTest, InvalidChunkedTrailers) {
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "0\r\nHost: example.com\r\n\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = POST_Req + CHUNKED + "0\r\nExpect: 100-continue\r\n\r\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}
