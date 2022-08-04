#include <gtest/gtest.h>
#include <string>

#include "../exception.hpp"
#include "../header_field_validator.hpp"
#include "../request.hpp"

static string RL = "GET /hello.txt HTTP/1.1\r\n";
static string RL_Host = "GET /hello.txt HTTP/1.1\r\nHost: www.example.com\r\n";

TEST(RequestHeaderTest, ValidHeaders) {
	string req_str = RL_Host + "Expect: 100-continue\n\n";
	Request request1(req_str.c_str());
	HeaderFieldValidator header_validator;
	int status = -1;
	status = header_validator.Process(request1);
	EXPECT_EQ(status, hv_OK);

	req_str = RL_Host + "Transfer-Encoding: chunked\n\n";
	Request request2(req_str.c_str());
	status = header_validator.Process(request2);
	EXPECT_EQ(status, hv_MessageChunked);

	req_str = RL_Host + "Content-Length: 42\n\n";
	Request request3(req_str.c_str());
	status = header_validator.Process(request3);
	EXPECT_EQ(status, hv_MessageExpected);
	EXPECT_EQ(request3.content_length, 42);
}

TEST(RequestHeaderTest, InvalidHost) {
	// multiple Hosts
	EXPECT_THROW({
		string req_str = RL + "Host: www.example.com, www.example.net\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// missing Host
	EXPECT_THROW({
		string req_str = RL + "Expect: 100-continue\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	EXPECT_THROW({
		string req_str = RL + "Host: \n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// bad Host path
	EXPECT_THROW({
		string req_str = RL + "Host: /example.com\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
}

TEST(RequestHeaderTest, InvalidExpect) {
	EXPECT_THROW({
		string req_str = RL_Host + "Expect: 101-continue\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, ExpectationFailedTypeException);
}

TEST(RequestHeaderTest, InvalidContentEncoding) {
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Encoding: gzip\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, UnsupportedMediaTypeException);
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Encoding: \n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, UnsupportedMediaTypeException);
}

TEST(RequestHeaderTest, InvalidTransferEncoding) {
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = RL_Host + "Transfer-Encoding: compress\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, NotImplementedException);
	// not-implemented transfer encoding format
	EXPECT_THROW({
		string req_str = RL_Host + "Transfer-Encoding: compress, chunked\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, NotImplementedException);
	// Content-Length also defined
	EXPECT_THROW({
		string req_str = RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
}

TEST(RequestHeaderTest, InvalidContentLength) {
	// invalid value (lower limit)
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Length: -42\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// invalid value (upper limit)
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Length: 1048577\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// invalid value
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Length: 42a\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// multiple different values
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Length: 42, 53\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// multiple identical values
	EXPECT_THROW({
		string req_str = RL_Host + "Content-Length: 42, 42\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
	// Transfer-Encoding also defined
	EXPECT_THROW({
		string req_str = RL_Host + "Transfer-Encoding: chunked\nContent-Length: 42\n\n";
		Request request(req_str.c_str());
		HeaderFieldValidator header_validator;

		header_validator.Process(request);
	}, BadRequestException);
}
