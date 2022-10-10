#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/config/directive_validation/directive_validation.hpp"
#include "../../src/request/request.hpp"
#include "../../src/cgi/cgi.hpp"
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

/////////////////////////////////////
//** MODULE CGI - GENERIC TESTS  **//
/////////////////////////////////////

std::string content = "Content-type:text/html\r\n\r\n\n<html>\n<head><title>My First CGI Program</title></head>\n<body>\n<p> Hello Program!! </p>\n</body>\n</html>\n";

TEST(CGITesting, valid) {
{
	NginxConfig config("config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.Setup(&request));
	EXPECT_EQ(test.Execute(), 200);
	size_t last_nl = test.GetContent().find_last_of('\n');
	std::string test_content = test.GetContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, content);

	EXPECT_EQ(test.GetContent(), content);
}
}
TEST(CGITesting, valid2) {
{
	NginxConfig config("config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	size_t result;
	EXPECT_TRUE(test.Setup(&request));
	result = test.Execute();
	std::cout << "result: " << result << std::endl;
	EXPECT_EQ(result, 200);
	size_t last_nl = test.GetContent().find_last_of('\n');
	std::string test_content = test.GetContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, content);
	EXPECT_EQ(test.GetContent(), content);
}
{
	NginxConfig config("config_files/cgi_testers/CGI_test.conf");
	
	Request request(&config);
	request.Parse("GET /cgi-bin/test.cgi HTTP/1.1\r\nHost: localhost\n\n");
	CGI test;
	EXPECT_TRUE(test.Setup(&request));
	EXPECT_EQ(test.Execute(), 200);
	size_t last_nl = test.GetContent().find_last_of('\n');
	// std::string test_cgi_content = "Content-type:text/html\r\n\r\n\n<html>\n<head><title>My First CGI Program</title></head>\n<body>\n<p> Hello Program!! </p>\n</body>\n</html>\nNumber of arguments: 1 arguments.\nArgument List: ['/Users/nhariman/codam/webserv/src/cgi/cgi_test/build/cgi-bin/test.cgi']\n";
	std::string test_cgi_content = "Content-type:text/html\r\n\r\n\n<html>\n<head><title>My First CGI Program</title></head>\n<body>\n<p> Hello Program!! </p>\n</body>\n</html>\nNumber of arguments: 1 arguments.\n";
	// std::string test_cgi_content = "";
	std::string test_content = test.GetContent().substr(0, last_nl + 1);
	EXPECT_EQ(test_content, test_cgi_content);
	EXPECT_EQ(test.GetContent(), test_cgi_content);
}
}

TEST(CGITESTING, invalid) {
	{
		NginxConfig config("config_files/cgi_testers/1_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_THROW(test.Setup(&request), NotFoundException);
	}
	{
		NginxConfig config("config_files/cgi_testers/1_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_THROW({test.Setup(&request);}, NotFoundException);
	}
	{
		NginxConfig config("config_files/cgi_testers/2_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_THROW(test.Setup(&request), NotFoundException);
	}
	{
		NginxConfig config("config_files/cgi_testers/2_arg_invalid_path.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_THROW(test.Setup(&request), NotFoundException);
	}
	{
		NginxConfig config("config_files/cgi_testers/2_arg_cgi_no_exist.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");
		CGI test;
		EXPECT_THROW(test.Setup(&request), NotFoundException);
	}
	{
		NginxConfig config("config_files/cgi_testers/2_arg_cgi_no_exist.conf");
	
		Request request(&config);
		request.Parse("GET /cgi-bin/test.py HTTP/1.1\r\nHost: localhost\n\n");
		CGI blo;
		EXPECT_THROW(blo.Setup(&request), NotFoundException);
	}
}

/////////////////////////////////////////////////////
//** MODULE CGI - TWO ARGUMENTS DIRECTED TESTING **//
////////////////////////////////////////////////////

TEST(CGITESTING_two_arguments, valid) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_two_arguments, req_directory_conf_directory) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_two_arguments, req_directory_conf_file) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET2.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}


// CGI TESTING TWO ARGUMENTS

TEST(CGITESTING_two_arguments, req_file_conf_directory) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_two_arguments, req_file_conf_file) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET2.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_two_arguments, wrong_extension_in_request) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pa?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}

TEST(CGITESTING_two_arguments, wrong_extension_in_config) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET3.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}

TEST(CGITESTING_two_arguments, executable_not_found) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET4.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}


////////////////////////////////////////////////////
//** MODULE CGI - ONE ARGUMENT DIRECTED TESTING **//
////////////////////////////////////////////////////

TEST(CGITESTING_ONE_argument, valid) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET5.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_ONE_argument, req_directory_conf_directory) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET5.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_ONE_argument, req_directory_conf_file) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET6.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/ HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_ONE_argument, req_file_conf_directory) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET5.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_ONE_argument, req_file_conf_file) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched '' for ''<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET7.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		get.Setup(&request);
		get.Execute();
		EXPECT_EQ(get.GetContent(), get_content);
	}
}

TEST(CGITESTING_one_argument, wrong_extension_in_request) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET7.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pa?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}

TEST(CGITESTING_ONE_argument, wrong_extension_in_config) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET8.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}

TEST(CGITESTING_ONE_argument, executable_incompatible) {
	std::string get_content;
	get_content = "Content-type:text/html\r\n\r\n<html><head><title>GeeksForGeeks - Get Method</title></head><body><h3>Hello You searched 'Web' for 'music'<br>\nFew Matches Found!<br>\n<br>\nMatch 1<br>\nMatch 2<br>\nMatch 3<br>\nMatch 4<br>\netc.....</h3></body></html>";

	{
		NginxConfig config("config_files/cgi_testers/CGI_GET9.conf");
		Request request(&config);
		request.Parse("GET /cgi-bin/get_query.pl?q=music&l=Web HTTP/1.1\r\nHost: localhost\n\n");

		CGI get;
		EXPECT_THROW(get.Setup(&request), NotFoundException);
	}
}
