#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../request.hpp"

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/src/request/testing/default.conf");

// Helper function that calls Request::Parse with c-string conversion of passed string.
static void	ParseChunked(Request& request, string const& req_str) {
	request.Parse(req_str.c_str());
}

TEST(RequestChunkedTest, ValidSplitHeaders) {
	Request request(&config);

	ParseChunked(request, POST_Req);
	ParseChunked(request, CHUNKED);
	ParseChunked(request, "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitHeadersMid) {
	Request request(&config);

	ParseChunked(request, POST_Req + "Transfer-Encod");
	ParseChunked(request, "ing: chunked\n\n");
	ParseChunked(request, "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitEmptyLine) {
	Request request(&config);

	ParseChunked(request, POST_Req + "Transfer-Encoding: chunked\r\n");
	ParseChunked(request, "\r\n");
	ParseChunked(request, "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitCRLF) {
	Request request(&config);

	ParseChunked(request, POST_Req + "Transfer-Encoding: chunked\r\n\r");
	ParseChunked(request, "\n4\r\nWiki\r");
	ParseChunked(request, "\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n");

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitDataCRLF) {
	Request request(&config);

	ParseChunked(request, POST_Req + "Transfer-Encoding: chunked\r\n\r");
	ParseChunked(request, "\n4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r");
	ParseChunked(request, "\n\r\nchunks.\r\n0\r\n\r\n");

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitHeadersCRLF) {
	Request request(&config);
	ParseChunked(request,  "GET /hello HTTP/1.1\r\nHost: localhost\r\nAccept: text/html\r");
	ParseChunked(request, "\n\r\n");

	EXPECT_EQ(request.GetField("host"), "localhost");
	EXPECT_EQ(request.GetField("Accept"), "text/html");
}

TEST(RequestChunkedTest, InvalidCRLF) {
	EXPECT_THROW({
		Request request(&config);
		ParseChunked(request, "GET /hello HTTP/1.1\r");
		ParseChunked(request, "\r\nHost: localhost\r\n\r\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		ParseChunked(request, POST_Req + "Transfer-Encoding: chunked\r\n\r");
		ParseChunked(request, "\r\n0\r\n\r\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		ParseChunked(request, POST_Req);
		ParseChunked(request, "Transfer-Encoding: chunked\r\n\r");
		ParseChunked(request, "\r\n0\r\n\r\n");
	}, BadRequestException);
	EXPECT_THROW({
		Request request(&config);
		ParseChunked(request,  "GET /hello HTTP/1.1\r\nHost: localhost\r\nAccept: text/html\r");
		ParseChunked(request, "\r\n\r\n");
	}, BadRequestException);
}
