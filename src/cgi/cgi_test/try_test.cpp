#include <gtest/gtest.h>
#include "../../config/nginx_config.hpp"
#include "../../config/directive_validation/directive_validation.hpp"
#include "../../request/request.hpp"
#include "../cgi.hpp"
# include <map>
#include <string>
#include <vector>

// Test syntax
/*
		TEST(TestSuiteName, TestName) {
		... test body ...
		}
*/

//////////////////////////////
//** MODULE CGI  **//
//////////////////////////////

TEST(CGITesting, valid) {
{
	NginxConfig config("../../../../config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.setup(&request));
	EXPECT_EQ(test.execute(), 0);
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
}
{
	NginxConfig config("../../../../config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/test.cgi HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.setup(&request));
	EXPECT_EQ(test.execute(), 0);
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
		NginxConfig config("../../../../config_files/cgi_testers/2_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
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
}
