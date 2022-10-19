#include <gtest/gtest.h>
#include <string>

#include "../../src/err/exception.hpp"
#include "../../src/request/request_validator.hpp"
#include "../../src/request/request.hpp"

using namespace std;

// defined in gtest_request_message.cpp
int	ConstructAndGetStatus(std::string const& req_str);

static string GET_RL = "GET /hello.txt HTTP/1.1\r\n";
static string GET_RL_Host = "GET /hello.txt HTTP/1.1\r\nHost: localhost\r\n";
static string DEL_RL_Host = "DELETE /hello HTTP/1.1\r\nHost: localhost\r\n";
static string POST_RL_Host = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";

static NginxConfig config("../default.conf");

// Helper function used by ValidHeaders test to construct and call
// RequestValidator on passed request string. Returns result of
// RequestValidator::Process().
static int	ConstructAndProcess(std::string req_str) {
	Request request(&config);
	request.Parse(req_str.c_str());
	TargetConfig	target_config;
	RequestValidator header_validator(&config, &target_config);

	return header_validator.Process(request);
}

TEST(RequestHeaderValidatorTest, ValidHeaders) {
	int status = -1;
	status = ConstructAndProcess(GET_RL_Host + "Expect: 100-continue\n\n");
	EXPECT_EQ(status, hv_Done);

	status = ConstructAndProcess(GET_RL_Host + "Content-Length: 0\n\n");
	EXPECT_EQ(status, hv_Done);

	status = ConstructAndProcess(DEL_RL_Host + "Content-Length: 0\n\n");
	EXPECT_EQ(status, hv_Done);

	// message is missing final empty line because when message is complete,
	// ChunkedHandler clears chunked-related headers and
	// RequestValidator will return Done.
	status = ConstructAndProcess(POST_RL_Host + "Transfer-Encoding: chunked\n\n0\r\n");
	EXPECT_EQ(status, hv_MessageChunked);

	status = ConstructAndProcess(POST_RL_Host + "Content-Length: 5\n\nHello");
	EXPECT_EQ(status, hv_MessageExpected);
}

static Request::Status	ConstructAndGetRequestStatus(std::string req_str) {
	Request request(&config);
	request.Parse(req_str.c_str());

	return request.GetRequestStatus();
}

TEST(RequestHeaderValidatorTest, ValidExpect) {
	Request::Status status;
	string expect_rq = POST_RL_Host + "Expect: 100-continue\n";
	
	status = ConstructAndGetRequestStatus(expect_rq + "\r\n");
	EXPECT_EQ(status, Request::Status::Complete);

	status = ConstructAndGetRequestStatus(expect_rq + "Content-Length: 5\n\n");
	EXPECT_EQ(status, Request::Status::Expect);

	status = ConstructAndGetRequestStatus(expect_rq + "Content-Length: 5\n\nHello");
	EXPECT_EQ(status, Request::Status::Complete);

	status = ConstructAndGetRequestStatus(expect_rq + "Content-Length: 5\n\nHel");
	EXPECT_EQ(status, Request::Status::Incomplete);

	status = ConstructAndGetRequestStatus(expect_rq + "Transfer-Encoding: chunked\n\n");
	EXPECT_EQ(status, Request::Status::Expect);

	status = ConstructAndGetRequestStatus(expect_rq + "Transfer-Encoding: chunked\n\n0");
	EXPECT_EQ(status, Request::Status::Incomplete);

	status = ConstructAndGetRequestStatus(expect_rq + "Transfer-Encoding: chunked\n\n0\n\n");
	EXPECT_EQ(status, Request::Status::Complete);
}

TEST(RequestHeaderValidatorTest, InvalidHost) {
	// multiple Hosts
	string req_str = GET_RL + "Host: localhost, www.example.net\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	// missing Host
	req_str = GET_RL + "Expect: 100-continue\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	req_str = GET_RL + "Host: \n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	// bad Host path
	req_str = GET_RL + "Host: /example.com\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
}

TEST(RequestHeaderValidatorTest, InvalidExpect) {
	string req_str = GET_RL_Host + "Expect: 101-continue\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 417); // Expectation Failed error
}

TEST(RequestHeaderValidatorTest, InvalidContentEncoding) {
	string req_str = POST_RL_Host + "Content-Encoding: gzip\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 415); // Unsupported Media Type error


	req_str = POST_RL_Host + "Content-Encoding: \n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 415); // Unsupported Media Type error
}

TEST(RequestHeaderValidatorTest, InvalidTransferEncoding) {
	// not-implemented transfer encoding format
	string req_str = POST_RL_Host + "Transfer-Encoding: compress\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 501); // Not Implemented error

	// not-implemented transfer encoding format
	req_str = POST_RL_Host + "Transfer-Encoding: compress, chunked\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 501); // Not Implemented error

	// T-E definition for not-allowed method
	req_str = GET_RL_Host + "Transfer-Encoding: chunked\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	// Content-Length also defined
	req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
}

TEST(RequestHeaderValidatorTest, InvalidContentLength) {
	// C-L definition for not-allowed method
	string req_str = GET_RL_Host + "Content-Length: 42\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error

	// invalid value (lower limit)
	req_str = POST_RL_Host + "Content-Length: -42\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	// invalid value (upper limit)
	req_str = POST_RL_Host + "Content-Length: 104857600\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 413); // Payload Too Large error
	
	// invalid value
	req_str = POST_RL_Host + "Content-Length: 42a\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	// multiple different values
	req_str = POST_RL_Host + "Content-Length: 42, 53\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	// multiple identical values
	req_str = POST_RL_Host + "Content-Length: 42, 42\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
	// Transfer-Encoding also defined
	req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 400); // Bad Request error
	
}

// reliant on specific default.conf file used at top.
TEST(RequestHeaderValidatorTest, InvalidMethod) {
	string req_str = "DELETE /hello.txt HTTP/1.1\nHost: localhost\nContent-Length: 0\n\n";
	int status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 405); // Method Not Allowed error
	
	req_str = "POST /nonexist HTTP/1.1\nHost: localhost\nContent-Length: 0\n\n";
	status = ConstructAndGetStatus(req_str);
	EXPECT_EQ(status, 405); // Method Not Allowed error
	
}
