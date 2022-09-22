#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

#define custom_err_page_path "/Users/mjiam/Desktop/42_projects/webserv/foodserv/html/error/custom_error_test.html"

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");

// config defines custom error_page for 405: Method Not Allowed error.
// /dog location block only allows GET and POST.
TEST(ResponseErrorTest, CustomError) {
	Connection connection(42, &config);

	connection.Receive("DELETE /dog HTTP/1.1\r\nHost: localhost\n\n");
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 405);

	std::istream* orig_file = new std::ifstream(custom_err_page_path);
	std::istream* response_file = response.GetFileStream();
	EXPECT_EQ(orig_file->tellg(), response_file->tellg());
	delete orig_file;
}