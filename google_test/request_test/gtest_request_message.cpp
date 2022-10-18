#include <gtest/gtest.h>
#include <string>

#include "../../src/err/exception.hpp"
#include "../../src/request/request.hpp"

using namespace std;

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/request_test/default.conf");

// Helper function that calls Request::Parse with c-string conversion of passed string.
void	ParseChunked(Request& request, string const& req_str) {
	request.Parse(req_str.c_str());
}

// Helper function used to construct Request objects with passed request string.
// Returns status code of request.
int	ConstructAndGetStatus(std::string const& req_str) {
	Request request(&config);
	request.Parse(req_str.c_str());
	return request.GetStatusCode();
}

// Helper function used to construct Request objects with passed string
// containing request message + a standard POST request line. Returns parsed message.
static string	ConstructAndGetMessage(std::string const& rest_of_header) {
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

	message = ConstructAndGetMessage("Content-Length: 0\r\n\n");
	EXPECT_EQ(message, "");
}

TEST(RequestMessageTest, ValidMessageChunked) {
	string message;

	message = ConstructAndGetMessage(CHUNKED +
		"4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
	EXPECT_EQ(message, "Wikipedia in \r\n\r\nchunks.");

	message = ConstructAndGetMessage(CHUNKED + "0\r\n\r\n");
	EXPECT_EQ(message, "");
}

TEST(RequestMessageTest, ValidMessageNormalSplit) {
	Request request(&config);

	ParseChunked(request, POST_Req + "Content-Length: 19\r\n\nHello World!\n");
	ParseChunked(request, "Bye!\r\n");
	EXPECT_EQ(request.GetMessageBody(), "Hello World!\nBye!\r\n");
}

TEST(RequestMessageTest, ValidMessageChunkedSplitBySize) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED);
	ParseChunked(request, "4\r\nWiki\r\n");
	ParseChunked(request, "6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n");
	ParseChunked(request, "0\r\n\r\n");

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

// Middle chunk is size 16 (hex 10) split over 2 reads.
TEST(RequestMessageTest, ValidMessageChunkedSplitBySizeHex) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED);
	ParseChunked(request, "4\r\nWiki\r\n");
	ParseChunked(request, "6\r\npedia \r\n1");
	ParseChunked(request, "0\r\nin \r\n\t\t\r\nchunks.\r\n");
	ParseChunked(request, "0\r\n\r\n");

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\t\t\r\nchunks.");
}

TEST(RequestMessageTest, ValidMessageChunkedSplitDataMid) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED);
	ParseChunked(request, "4\r\nWiki\r\n");
	ParseChunked(request, "6\r\npedia \r\nE\r\ni");
	ParseChunked(request, "n \r\n\r\nchunks.\r\n0\r\n\r\n");
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestMessageTest, ValidMessageChunkedSplitSizeData) {
	Request request(&config);

	ParseChunked(request,  POST_Req + "Transfer-Encoding: chunked\r\n\r\n4\r\n");
	ParseChunked(request,  "Wiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestMessageTest, ValidMessageChunkedSplitLast) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED);
	ParseChunked(request, "4\r\nWiki\r\n");
	ParseChunked(request, "6\r\npedia \r\nE\r\ni");
	ParseChunked(request, "n \r\n\r\nchunks.\r\n0\r");
	ParseChunked(request, "\n\r\n");
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestMessageTest, ValidMessageChunkedTrailers) {
	Request request1(&config);
	ParseChunked(request1, POST_Req + CHUNKED +
		"7\nChunks.\r\n0\r\nPrefer: return=representation\r\n\r\n");
	EXPECT_EQ(request1.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request1.GetField("Prefer"), "return=representation");

	Request request2(&config);
	ParseChunked(request2, POST_Req + CHUNKED +
		"7\nChunks.\r\n0\r\nPrefer: return=representation\r\nAccept: text/html\n\r\n");
	EXPECT_EQ(request2.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request2.GetField("Prefer"), "return=representation");
	EXPECT_EQ(request2.GetField("Accept"), "text/html");
}

TEST(RequestMessageTest, ValidMessageChunkedTrailersSplitValue) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED + "7\nChunks.\r\n0\r\nPrefer: return=");
	ParseChunked(request, "representation\r\n\r\n");
	EXPECT_EQ(request.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request.GetField("Prefer"), "return=representation");
}

TEST(RequestMessageTest, ValidMessageChunkedTrailersSplitName) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED + "7\nChunks.\r\n0\r\nPrefer: return=representation\r\n");
	ParseChunked(request, "Accept: text/html\n\r\n");
	EXPECT_EQ(request.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request.GetField("Prefer"), "return=representation");
	EXPECT_EQ(request.GetField("Accept"), "text/html");
}

TEST(RequestMessageTest, ValidMessageChunkedTrailersSplitCRLF) {
	Request request(&config);

	ParseChunked(request, POST_Req + CHUNKED + "7\nChunks.\r\n0\r\nPrefer: return=representation\r");
	ParseChunked(request, "\nAccept: text/html\n\r\n");
	EXPECT_EQ(request.GetMessageBody(), "Chunks.");
	EXPECT_EQ(request.GetField("Prefer"), "return=representation");
	EXPECT_EQ(request.GetField("Accept"), "text/html");
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

TEST(RequestMessageTest, ValidPOSTRequestQuery) {
	Request	request(&config);
	string message = "POST /cgi-bin/form.py HTTP/1.1\nHost: localhost\nContent-Length: 64\n";
	message += "Content-Type: application/x-www-form-urlencoded\n\n";
	message += "name=Joe%20User&id=42";

	request.Parse(message.c_str());
	EXPECT_EQ(request.GetQuery(), "name=Joe User&id=42");
}

TEST(RequestMessageTest, InvalidMessageWithoutCE) {
	// message without Content-Length
	int status = ConstructAndGetStatus(POST_Req + "\r\nHello World!");
	EXPECT_EQ(status, 411); // Length Required error
}

TEST(RequestMessageTest, InvalidMessageChunked) {
	// invalid line ending
	string req_str = POST_Req + CHUNKED + "0\r\r\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	// missing last chunk
	req_str = POST_Req + CHUNKED + "4\r\nBye!\r\n\r\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	// chunk size string exceeding 7 octet length limit.
	req_str = POST_Req + CHUNKED + "10485760\r\n0\r\n\r\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 413); // Payload Too Large error

	// chunk size exceeding default 1,048,576B payload limit.
	// NOTE: doesn't work if config max client body size is specified higher.
	req_str = POST_Req + CHUNKED + "1048577\r\n0\r\n\r\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 413); // Payload Too Large error

	// chunk extension exceeding 8192B limit
	string ext(8193, 'a');
	req_str = POST_Req + CHUNKED + "0;" + ext + "\r\n\r\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 413); // Payload Too Large error
}

TEST(RequestMessageTest, InvalidMessageChunkedSplit) {
	// invalid line endings
	Request request1(&config);
	ParseChunked(request1, POST_Req + CHUNKED + "4\r");
	ParseChunked(request1, "\r\nBye!\r\n0\r\n\r\n");
	EXPECT_EQ(request1.GetStatusCode(), 400); // Bad Request error

	Request request2(&config);
	ParseChunked(request2, POST_Req + CHUNKED + "4\r\nBye!\r");
	ParseChunked(request2, "\r\n0\r\n\r\n");
	EXPECT_EQ(request2.GetStatusCode(), 400); // Bad Request error

	Request request3(&config);
	ParseChunked(request3, POST_Req + CHUNKED + "4\r\nBye!\r\n0\r");
	ParseChunked(request3, "\r\n\r\n");
	EXPECT_EQ(request3.GetStatusCode(), 400); // Bad Request error

	Request request4(&config);
	ParseChunked(request4, POST_Req + CHUNKED + "4\r\n");
	ParseChunked(request4, "Bye!\r\r\n0\r\n\r\n");
	EXPECT_EQ(request4.GetStatusCode(), 400); // Bad Request error

	Request request5(&config);
	ParseChunked(request5, POST_Req + CHUNKED + "4\r\n");
	ParseChunked(request5, "Bye!\r\n0\r\r\n");
	EXPECT_EQ(request5.GetStatusCode(), 400); // Bad Request error
}

TEST(RequestMessageTest, InvalidChunkedTrailers) {
	// illegal trailer header fields
	string req_str = POST_Req + CHUNKED + "0\r\nHost: example.com\r\n\r\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = POST_Req + CHUNKED + "0\r\nExpect: 100-continue\r\n\r\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
}

TEST(RequestMessageTest, InvalidChunkedTrailersSplit) {
	// bad CRLF
	Request request1(&config);
	ParseChunked(request1, POST_Req + CHUNKED + "0\r\n");
	ParseChunked(request1, "Accept: text/html\r");
	ParseChunked(request1, "\r\n\r\n");
	EXPECT_EQ(request1.GetStatusCode(), 400); // Bad Request error

	Request request2(&config);
	ParseChunked(request2, POST_Req + CHUNKED + "0\r\n");
	ParseChunked(request2, "Accept: text/html\r\nPrefer: return=representation\r");
	ParseChunked(request2, "\r\n\r\n");
	EXPECT_EQ(request2.GetStatusCode(), 400); // Bad Request error
}
