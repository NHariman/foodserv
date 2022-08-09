#include "header_field_validator.hpp"

HeaderFieldValidator::HeaderFieldValidator() : _status(hv_OK) {}

HeaderFieldValidator::~HeaderFieldValidator() {}

HeaderStatus	HeaderFieldValidator::Process(NginxConfig* config, Request& request) {
	_status = hv_OK;

	if (ValidHost(request.GetField("host"))
			&& ValidExpect(request.GetField("expect"))
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidTransferEncoding(request.content_length,
										request.GetField("transfer-encoding"))
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

// If Transfer-Encoding is define, only "chunked" value is accepted.
bool	HeaderFieldValidator::ValidTransferEncoding(ssize_t content_length_count,
													string transfer_encoding) {
	if (transfer_encoding != NO_VAL) {
		// if Content-Length was also defined
		if (content_length_count != -1)
			throw BadRequestException(
				"Cannot have both Content-Length and Transfer-Encoding headers");
		if (transfer_encoding == "chunked")
			_status = hv_MessageChunked;
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

	// if invalid value
	request.content_length = std::stoll(content_length);
	size_t	limit = MBToBytes(config->GetMaxBodySize(host, target));
	
	if (request.content_length < 0 || request.content_length > limit)
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

// Only exactly 1 Content-Length definition is accepted.
bool	HeaderFieldValidator::ValidContentLength(NginxConfig* config,
													Request& request) {
	string	content_length = request.GetField("content-length");

	if (content_length != NO_VAL) {
		CheckIfTransferEncodingDefined(_status);
		CheckForMultipleValues(content_length);
		CheckContentLengthValue(config, request);			
		_status = hv_MessageExpected;
	}
	return true;
}

bool	HeaderFieldValidator::ValidMethod(NginxConfig* config, Request& request) {
	string	host = request.GetField("host");
	string	target = request.GetTarget();
	string	method = request.GetMethod();

	return config->IsAllowedMethod(host, target, method);
}
