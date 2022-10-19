#include <gtest/gtest.h>
#include <string>

#include "../../src/err/exception.hpp"
#include "../../src/request/request.hpp"

using namespace std;

// defined in gtest_request_message.cpp
void	ParseChunked(Request& request, string const& req_str);

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config("../default.conf");

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
	Request request1(&config);
	ParseChunked(request1, "GET /hello HTTP/1.1\r");
	ParseChunked(request1, "\r\nHost: localhost\r\n\r\n");
	EXPECT_EQ(request1.GetStatusCode(), 400); // Bad Request error

	Request request2(&config);
	ParseChunked(request2, POST_Req + "Transfer-Encoding: chunked\r\n\r");
	ParseChunked(request2, "\r\n0\r\n\r\n");
	EXPECT_EQ(request2.GetStatusCode(), 400); // Bad Request error

	Request request3(&config);
	ParseChunked(request3, POST_Req);
	ParseChunked(request3, "Transfer-Encoding: chunked\r\n\r");
	ParseChunked(request3, "\r\n0\r\n\r\n");
	EXPECT_EQ(request3.GetStatusCode(), 400); // Bad Request error

	Request request4(&config);
	ParseChunked(request4,  "GET /hello HTTP/1.1\r\nHost: localhost\r\nAccept: text/html\r");
	ParseChunked(request4, "\r\n\r\n");
	EXPECT_EQ(request4.GetStatusCode(), 400); // Bad Request error
}
