#include "header_field_validator.hpp"

HeaderFieldValidator::HeaderFieldValidator() : _status(hv_OK) {}

HeaderFieldValidator::~HeaderFieldValidator() {}

HeaderStatus	HeaderFieldValidator::Process(NginxConfig* config, Request& request) {
	_status = hv_OK;

	if (ValidHost(request.GetField("host"))
			&& ValidExpect(request.GetField("expect"))
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidTransferEncoding(request)
			&& ValidContentLength(config, request)
			&& ValidMethod(config, request))
		return _status;
	return hv_Bad;
}

// Only exactly 1 Host definition is accepted.
bool	HeaderFieldValidator::ValidHost(string host) {
	if (host == NO_VAL)
		throw BadRequestException("Host header mandatory");
	try {
		URIHostParser	parser;
		string			host_parsed;

		// Checks if Host value is valid path
		parser.Parse(host_parsed, host);
	}
	catch (...) {
		throw;
	}
	return true;
}

// Only accepts "100-continue" for Expect header.
bool	HeaderFieldValidator::ValidExpect(string expect) {
	if (expect != NO_VAL && expect != "100-continue")
		throw ExpectationFailedTypeException();
	else
		return true;
}

// Does not accept any definition of Content-Encoding header.
bool	HeaderFieldValidator::ValidContentEncoding(string content_encoding) {
	if (content_encoding != NO_VAL)
		throw UnsupportedMediaTypeException();
	else
		return true;
}

// Used by ValidContentLength & ValidTransferEncoding to check if 
// Content-Length & Transfer-Encoding (and therefore presence of payload body)
// is allowed for specified method.
// Of server-allowed methods, only POST is accepted here
// (and is actually expected, even if 0 for empty payload body).
static void	CheckAllowedMethod(string method) {
	if (method != "POST")
		throw BadRequestException("Payload body not allowed for method");
}

// If Transfer-Encoding is define, only "chunked" value is accepted.
bool	HeaderFieldValidator::ValidTransferEncoding(Request& request) {
	string	transfer_encoding = request.GetField("transfer-encoding");

	if (transfer_encoding != NO_VAL) {
		// if Content-Length was also defined
		if (request.content_length != -1)
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

static size_t GetMaxBodySize(string host, string target) {
	(void)host, (void)target;

	return 1;
} // TODO: remove once config method implemented

// Used by ValidContentLength to check for valid values.
static void	CheckContentLengthValue(NginxConfig* config,
									Request& request) {
	string	content_length = request.GetField("content-length");
	string	host = request.GetField("host");
	string	target = request.GetTarget();

	// non-digit value
	if (!IsValidString(isdigit, content_length))
		throw BadRequestException("Invalid Content-Length value");

	// if invalid value
	request.content_length = std::stoll(content_length);
	// size_t	limit = MBToBytes(config->GetMaxBodySize(host, target));
	(void)config;
	size_t	limit = MBToBytes(GetMaxBodySize(host, target));
	
	if (request.content_length < 0 || (size_t)request.content_length > limit)
		throw BadRequestException("Invalid Content-Length value");
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
bool	HeaderFieldValidator::ValidContentLength(NginxConfig* config,
													Request& request) {
	string	content_length = request.GetField("content-length");

	if (content_length != NO_VAL) {
		CheckIfTransferEncodingDefined(_status);
		CheckForMultipleValues(content_length);
		CheckContentLengthValue(config, request);	
		CheckAllowedMethod(request.GetMethod());
		_status = hv_MessageExpected;
	}
	return true;
}

static bool IsAllowedMethod(string host, string target, string method) {
	(void)host, (void)target, (void)method;
	return true;
} // TODO: remove once config method implemented

bool	HeaderFieldValidator::ValidMethod(NginxConfig* config, Request& request) {
	string	host = request.GetField("host");
	string	target = request.GetTarget();
	string	method = request.GetMethod();

	// return config->IsAllowedMethod(host, target, method);
	(void)config;
	return IsAllowedMethod(host, target, method);
}
