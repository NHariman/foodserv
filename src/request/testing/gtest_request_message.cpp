#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../request.hpp"

static string POST_Req = "POST /hello HTTP/1.1\r\nHost: www.example.com\r\n";

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