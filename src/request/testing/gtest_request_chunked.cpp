#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../request.hpp"

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";
static string CHUNKED = "Transfer-Encoding: chunked\n\n";

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/config_files/default.conf");

TEST(RequestChunkedTest, ValidSplitHeaders) {
	Request request(&config);

	string req_str = POST_Req;
	request.Parse(req_str.c_str());

	req_str = CHUNKED;
	request.Parse(req_str.c_str());

	req_str = "4\r\nWiki\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
	request.Parse(req_str.c_str());
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitHeadersMid) {
	Request request(&config);

	string req_str = POST_Req + "Transfer-Encod";
	request.Parse(req_str.c_str());

	req_str = "ing: chunked\n\n";
	request.Parse(req_str.c_str());

	req_str = "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
	request.Parse(req_str.c_str());
	
	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitEmptyLine) {
	Request request(&config);

	string req_str = POST_Req + "Transfer-Encoding: chunked\r\n";
	request.Parse(req_str.c_str());

	req_str = "\r\n";
	request.Parse(req_str.c_str());

	req_str = "4\r\nWiki\r\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
	request.Parse(req_str.c_str());

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}

TEST(RequestChunkedTest, ValidSplitCRLF) {
	Request request(&config);

	string req_str = POST_Req + "Transfer-Encoding: chunked\r\n\r";
	request.Parse(req_str.c_str());

	req_str = "\n4\r\nWiki\r";
	request.Parse(req_str.c_str());

	req_str = "\n6\r\npedia \r\nE\r\nin \r\n\r\nchunks.\r\n0\r\n\r\n";
	request.Parse(req_str.c_str());

	EXPECT_EQ(request.GetMessageBody(), "Wikipedia in \r\n\r\nchunks.");
}
