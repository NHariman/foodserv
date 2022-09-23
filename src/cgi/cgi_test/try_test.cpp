#include <gtest/gtest.h>
#include "../../config/nginx_config.hpp"
#include "../../config/directive_validation/directive_validation.hpp"
#include "../../request/request.hpp"
#include "../cgi.hpp"
# include <map>
#include <string>
#include <vector>
#include <iostream>

// Test syntax
/*
		TEST(TestSuiteName, TestName) {
		... test body ...
		}
*/

//////////////////////////////
//** MODULE CGI  **//
//////////////////////////////

std::string content = "Content-type:text/html\r\n\r\n\n<html>\n<head><title>My First CGI Program</title></head>\n<body>\n<p> Hello Program!! </p>\n</body>\n</html>\n";

TEST(CGITesting, valid) {
{
	NginxConfig config("../../../../config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.setup(&request));
	EXPECT_EQ(test.execute(), 0);
	size_t last_nl = test.getContent().find_last_of('\n');
	std::string test_content = test.getContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, content);
}
}
TEST(CGITesting, valid2) {
{
	NginxConfig config("../../../../config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.setup(&request));
	EXPECT_EQ(test.execute(), 0);
	size_t last_nl = test.getContent().find_last_of('\n');
	std::string test_content = test.getContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, content);
}
{
	NginxConfig config("../../../../config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/test.cgi HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.setup(&request));
	EXPECT_EQ(test.execute(), 0);
	size_t last_nl = test.getContent().find_last_of('\n');
	std::string test_cgi_content = "Content-type:text/html\r\n\r\n\n<html>\n<head><title>My First CGI Program</title></head>\n<body>\n<p> Hello Program!! </p>\n</body>\n</html>\nNumber of arguments: 1 arguments.\nArgument List: ['/Users/nhariman/codam/webserv/src/cgi/cgi_test/build/cgi-bin/test.cgi']\n";

	std::string test_content = test.getContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, test_cgi_content);
}
}

TEST(CGITESTING, invalid) {
	{
		NginxConfig config("../../../../config_files/cgi_testers/1_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
	{
		NginxConfig config("../../../../config_files/cgi_testers/1_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
	{
		NginxConfig config("../../../../config_files/cgi_testers/2_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
	{
		NginxConfig config("../../../../config_files/cgi_testers/2_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
	{
		NginxConfig config("../../../../config_files/cgi_testers/2_arg_cgi_no_exist.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
	{
		NginxConfig config("../../../../config_files/cgi_testers/2_arg_cgi_no_exist.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_FALSE(test.setup(&request));
	}
}
