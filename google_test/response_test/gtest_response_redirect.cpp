#include <gtest/gtest.h>
#include "../../src/config/nginx_config.hpp"
#include "../../src/connection/connection.hpp"
#include "../../src/response/response.hpp"

using namespace std;

static NginxConfig config("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/default.conf");
static NginxConfig config_redir("/Users/mjiam/Desktop/42_projects/webserv/foodserv/google_test/response_test/redirect.conf");

// Context:
// /helloworld location block has a "return 307 localhost/hello" directive.
TEST(ResponseRedirectTest, LocationRedirect307) {
	Connection connection(42, &config);

	connection.Receive("GET /helloworld HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 307);
	EXPECT_EQ(response.GetReasonPhrase(), "Temporary Redirect");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), "localhost/hello");
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);
}

// Context:
// /test location block has a "return 301 localhost/" directive.
TEST(ResponseRedirectTest, LocationRedirect301) {
	Connection connection(42, &config);

	connection.Receive("GET /test HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 301);
	EXPECT_EQ(response.GetReasonPhrase(), "Moved Permanently");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), "localhost/");
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);
}

// Context:
// server block has a "return 307 localhost/new" directive.
TEST(ResponseRedirectTest, ServerRedirect307) {
	Connection connection(42, &config_redir);

	connection.Receive("GET / HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 307);
	EXPECT_EQ(response.GetReasonPhrase(), "Temporary Redirect");
	EXPECT_EQ(response.GetField("Allow"), NO_VAL);
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), NO_VAL);
	EXPECT_EQ(response.GetField("Location"), "localhost/new");
	EXPECT_EQ(response.GetField("Content-Length"), NO_VAL);
}

// Testing if server correctly returns error despite return directive.
// Context:
// /test location block only allows GET & POST.
TEST(ResponseRedirectTest, LocationRedirectError) {
	Connection connection(42, &config);

	connection.Receive("DELETE /test HTTP/1.1\r\nHost: localhost\n\n");
	
	Response const&	response = connection.DebugGetResponse();
	EXPECT_EQ(response.GetStatusCode(), 405);
	EXPECT_EQ(response.GetReasonPhrase(), "Method Not Allowed");
	EXPECT_EQ(response.GetField("Allow"), "GET, POST");
	EXPECT_EQ(response.GetField("Connection"), "close");
	EXPECT_EQ(response.GetField("Content-Type"), "text/html");
	EXPECT_EQ(response.GetField("Location"), NO_VAL);
}
