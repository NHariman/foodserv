#include <gtest/gtest.h>
#include <string>

#include "../../err/exception.hpp"
#include "../request_validator.hpp"
#include "../request.hpp"

static string GET_RL = "GET /hello.txt HTTP/1.1\r\n";
static string GET_RL_Host = "GET /hello.txt HTTP/1.1\r\nHost: localhost\r\n";
static string DEL_RL_Host = "DELETE /hello HTTP/1.1\r\nHost: localhost\r\n";
static string POST_RL_Host = "POST /hello HTTP/1.1\r\nHost: localhost\r\n";

static NginxConfig config("/Users/mjiam/Desktop/42/webserv/foodserv/src/request/testing/default.conf");

// Helper function used by ValidHeaders test to construct and call
// RequestValidator on passed request string. Returns result of
// RequestValidator::Process().
static int	ConstructAndProcess(string req_str) {
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

static Request::Status	ConstructAndGetStatus(string req_str) {
	Request request(&config);
	request.Parse(req_str.c_str());

	return request.GetRequestStatus();
}

TEST(RequestHeaderValidatorTest, ValidExpect) {
	Request::Status status;
	string expect_rq = POST_RL_Host + "Expect: 100-continue\n";
	
	status = ConstructAndGetStatus(expect_rq + "\r\n");
	EXPECT_EQ(status, Request::Status::Complete);

	status = ConstructAndGetStatus(expect_rq + "Content-Length: 5\n\n");
	EXPECT_EQ(status, Request::Status::Expect);

	status = ConstructAndGetStatus(expect_rq + "Content-Length: 5\n\nHello");
	EXPECT_EQ(status, Request::Status::Complete);

	status = ConstructAndGetStatus(expect_rq + "Content-Length: 5\n\nHel");
	EXPECT_EQ(status, Request::Status::Incomplete);

	status = ConstructAndGetStatus(expect_rq + "Transfer-Encoding: chunked\n\n");
	EXPECT_EQ(status, Request::Status::Expect);

	status = ConstructAndGetStatus(expect_rq + "Transfer-Encoding: chunked\n\n0");
	EXPECT_EQ(status, Request::Status::Incomplete);

	status = ConstructAndGetStatus(expect_rq + "Transfer-Encoding: chunked\n\n0\n\n");
	EXPECT_EQ(status, Request::Status::Complete);
}

TEST(RequestHeaderValidatorTest, InvalidHost) {
	// multiple Hosts
	EXPECT_THROW({
		string req_str = GET_RL + "Host: localhost, www.example.net\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// missing Host
	EXPECT_THROW({
		string req_str = GET_RL + "Expect: 100-continue\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = GET_RL + "Host: \n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// bad Host path
	EXPECT_THROW({
		string req_str = GET_RL + "Host: /example.com\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}

TEST(RequestHeaderValidatorTest, InvalidExpect) {
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Expect: 101-continue\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, ExpectationFailedTypeException);
}

TEST(RequestHeaderValidatorTest, InvalidContentEncoding) {
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Encoding: gzip\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, UnsupportedMediaTypeException);
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Encoding: \n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, UnsupportedMediaTypeException);
}

TEST(RequestHeaderValidatorTest, InvalidTransferEncoding) {
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: compress\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, NotImplementedException);
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: compress, chunked\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, NotImplementedException);
	// T-E definition for not-allowed method
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Transfer-Encoding: chunked\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// Content-Length also defined
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}

TEST(RequestHeaderValidatorTest, InvalidContentLength) {
	// C-L definition for not-allowed method
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Content-Length: 42\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// invalid value (lower limit)
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: -42\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// invalid value (upper limit)
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 104857600\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, PayloadTooLargeException);
	// invalid value
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42a\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// multiple different values
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42, 53\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// multiple identical values
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42, 42\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	// Transfer-Encoding also defined
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}

// reliant on specific default.conf file used at top.
TEST(RequestHeaderValidatorTest, InvalidMethod) {
	EXPECT_THROW({
		string req_str = "DELETE /hello.txt HTTP/1.1\nHost: localhost\nContent-Length: 0\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = "POST /nonexist HTTP/1.1\nHost: localhost\nContent-Length: 0\n\n";
		Request request(&config);
		request.Parse(req_str.c_str());
	}, BadRequestException);
}
