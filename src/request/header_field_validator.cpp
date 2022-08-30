#include "header_field_validator.hpp"
#include "request.hpp"

#define DEBUG 0 // TODO: REMOVE

HeaderFieldValidator::HeaderFieldValidator() : _status(hv_Done) {}

HeaderFieldValidator::~HeaderFieldValidator() {}

HeaderStatus	HeaderFieldValidator::Process(NginxConfig* config, Request& request) {
	_status = hv_Done;

	if (DEBUG) cout << "HeaderFieldValidator::Process\n";
	
	if (ValidHost(request.GetField("host"))
			&& ValidExpect(request)
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidTransferEncoding(request)
			&& ValidContentLength(config, request)
			&& ValidMethod(config, request))
		return _status;
	return hv_Bad;
}

// Only exactly 1 Host definition is accepted.
bool	HeaderFieldValidator::ValidHost(string host) {
	if (DEBUG) cout << "ValidHost\n";

	if (host == NO_VAL)
		throw BadRequestException("Host header mandatory");
	if (host.find(' ') != string::npos || host.find(',') != string::npos)
		throw BadRequestException("Multiple hosts not allowed");
	try {
		URIHostParser	parser;
		URI				uri;

		// Checks if Host value is valid path
		parser.Parse(uri, host);
	}
	catch (std::exception &e) {
		throw;
	}
	return true;
}

// Only accepts "100-continue" for Expect header.
bool	HeaderFieldValidator::ValidExpect(Request& request) {
	if (DEBUG) cout << "ValidExpect\n";

	string	expect = request.GetField("expect");

	if (expect != NO_VAL) {
		if (expect != "100-continue")
			throw ExpectationFailedTypeException();
		else
			request.SetStatus(Request::Status::Expect);
	}
	return true;
}

// Does not accept any definition of Content-Encoding header.
bool	HeaderFieldValidator::ValidContentEncoding(string content_encoding) {
	if (DEBUG) cout << "ValidContentEncoding\n";

	if (content_encoding != NO_VAL)
		throw UnsupportedMediaTypeException();
	else
		return true;
}

// Used by ValidContentLength & ValidTransferEncoding to check if 
// Content-Length & Transfer-Encoding (and therefore presence of payload body)
// is allowed for specified method.
// GET & DELETE may only have Content-Length of 0 and only POST may have
// other values (including 0 for empty payloads).
static void	CheckAllowedMethod(string method, size_t content_length = 1) {
	if (method != "POST" && content_length != 0)
		throw BadRequestException("Payload body not allowed for method");
}

// If Transfer-Encoding is define, only "chunked" value is accepted.
bool	HeaderFieldValidator::ValidTransferEncoding(Request& request) {
	if (DEBUG) cout << "ValidTransferEncoding\n";

	string	transfer_encoding = request.GetField("transfer-encoding");

	if (transfer_encoding != NO_VAL) {
		// if Content-Length was also defined
		if (request.GetField("content-length") != NO_VAL)
			throw BadRequestException(
				"Cannot have both Content-Length and Transfer-Encoding headers");
		if (transfer_encoding == "chunked") {
			CheckAllowedMethod(request.GetMethod());
			_status = hv_MessageChunked;
		}
		// if anything other than "chunked" encoding
		else
			throw NotImplementedException();
	}
	return true;
}

// Used by ValidContentLength to check for valid values.
static void	CheckContentLengthValue(NginxConfig* config,
									Request& request) {
	string	content_length = request.GetField("content-length");
	string	host = request.GetField("host");
	string	target = request.GetTarget();

	// non-digit value
	if (!IsValidString(isdigit, content_length))
		throw BadRequestException("Invalid Content-Length value");

	request.content_length = std::stoll(content_length);
	request.max_body_size = MBToBytes(config->GetMaxBodySize(host, target));
	
	// if invalid value
	if (request.content_length < 0)
		throw BadRequestException("Invalid Content-Length value");
	else if ((size_t)request.content_length > request.max_body_size)
		throw PayloadTooLargeException();
}

// Checks if multiple values defined for Content-Length.
static void	CheckForMultipleValues(string content_length) {
	if (content_length.find(',') != string::npos)
		throw BadRequestException(
			"Cannot have multiple Content-Length values");
}

// Checks if Transfer-Encoding & Content-Length are both defined.
static void	CheckIfTransferEncodingDefined(HeaderStatus status) {
	if (status == hv_MessageChunked)
		throw BadRequestException(
			"Cannot have both Content-Length and Transfer-Encoding headers");
}

// Only exactly 1 Content-Length definition is accepted
// and only for POST requests.
// Sets `content_length` and `max_body_size` attributes within Request.
bool	HeaderFieldValidator::ValidContentLength(NginxConfig* config,
													Request& request) {
	if (DEBUG) cout << "ValidContentLength\n";

	string	content_length = request.GetField("content-length");

	if (content_length != NO_VAL) {
		CheckIfTransferEncodingDefined(_status);
		CheckForMultipleValues(content_length);
		CheckContentLengthValue(config, request);
		CheckAllowedMethod(request.GetMethod(), request.content_length);
		if (request.content_length == 0)
			_status = hv_Done;
		else
			_status = hv_MessageExpected;
	}
	return true;
}

bool	HeaderFieldValidator::ValidMethod(NginxConfig* config, Request& request) {
	if (DEBUG) cout << "ValidMethod\n";

	string	host = request.GetField("host");
	string	target = request.GetTarget();
	string	method = request.GetMethod();

	return config->IsAllowedMethod(host, target, method);
}

#undef DEBUG // REMOVE