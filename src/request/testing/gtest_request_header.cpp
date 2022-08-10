#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../header_field_validator.hpp"
#include "../request.hpp"

static string GET_RL = "GET /hello.txt HTTP/1.1\r\n";
static string GET_RL_Host = "GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n";
static string POST_RL_Host = "POST /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n";

static NginxConfig config(NULL);

TEST(RequestHeaderTest, ValidHeaders) {
	string req_str = GET_RL_Host + "Expect: 100-continue\n\n";
	Request request1(&config, req_str.c_str());
	HeaderFieldValidator header_validator;
	int status = -1;
	status = header_validator.Process(&config, request1);
	EXPECT_EQ(status, hv_OK);

	req_str = POST_RL_Host + "Transfer-Encoding: chunked\n\n0";
	Request request2(&config, req_str.c_str());
	status = header_validator.Process(&config, request2);
	EXPECT_EQ(status, hv_MessageChunked);

	req_str = POST_RL_Host + "Content-Length: 5\n\nHello";
	Request request3(&config, req_str.c_str());
	status = header_validator.Process(&config, request3);
	EXPECT_EQ(status, hv_MessageExpected);
	EXPECT_EQ(request3.content_length, 5);
}

TEST(RequestHeaderTest, InvalidHost) {
	// multiple Hosts
	EXPECT_THROW({
		string req_str = GET_RL + "Host: www.example.com, www.example.net\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// missing Host
	EXPECT_THROW({
		string req_str = GET_RL + "Expect: 100-continue\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = GET_RL + "Host: \n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// bad Host path
	EXPECT_THROW({
		string req_str = GET_RL + "Host: /example.com\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
}

TEST(RequestHeaderTest, InvalidExpect) {
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Expect: 101-continue\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, ExpectationFailedTypeException);
}

TEST(RequestHeaderTest, InvalidContentEncoding) {
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Encoding: gzip\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, UnsupportedMediaTypeException);
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Encoding: \n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, UnsupportedMediaTypeException);
}

TEST(RequestHeaderTest, InvalidTransferEncoding) {
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: compress\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, NotImplementedException);
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: compress, chunked\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, NotImplementedException);
	// T-E definition for not-allowed method
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Transfer-Encoding: chunked\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// Content-Length also defined
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
}

TEST(RequestHeaderTest, InvalidContentLength) {
	// C-L definition for not-allowed method
	EXPECT_THROW({
		string req_str = GET_RL_Host + "Content-Length: 42\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// invalid value (lower limit)
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: -42\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// invalid value (upper limit)
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 1048577\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// invalid value
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42a\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// multiple different values
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42, 53\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// multiple identical values
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Content-Length: 42, 42\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
	// Transfer-Encoding also defined
	EXPECT_THROW({
		string req_str = POST_RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(&config, req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(&config, request);
	}, BadRequestException);
}
