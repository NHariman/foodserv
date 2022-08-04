#include "header_field_validator.hpp"

HeaderFieldValidator::HeaderFieldValidator() : _status(hv_OK) {}

HeaderFieldValidator::~HeaderFieldValidator() {}

HeaderStatus	HeaderFieldValidator::Process(Request& request) {
	_status = hv_OK;
	if (ValidHost(request.GetField("host"))
			&& ValidExpect(request.GetField("expect"))
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidTransferEncoding(request.content_length,
										request.GetField("transfer-encoding"))
			&& ValidContentLength(request.content_length,
									request.GetField("content-length")))
		return _status;
	return hv_Bad;
}

// Only exactly 1 Host definition is accepted.
bool HeaderFieldValidator::ValidHost(string host) {
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
bool HeaderFieldValidator::ValidExpect(string expect) {
	if (expect != NO_VAL && expect != "100-continue")
		throw ExpectationFailedTypeException();
	else
		return true;
}

// Does not accept any definition of Content-Encoding header.
bool HeaderFieldValidator::ValidContentEncoding(string content_encoding) {
	if (content_encoding != NO_VAL)
		throw UnsupportedMediaTypeException();
	else
		return true;
}

// If Transfer-Encoding is define, only "chunked" value is accepted.
bool HeaderFieldValidator::ValidTransferEncoding(ssize_t content_length_count,
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
static bool	ValidContentLengthValue(ssize_t& content_length_count,
												string content_length) {
	// non-digit value
	if (!IsValidString(isdigit, content_length))
		return false;

	// if invalid value
	content_length_count = std::stoll(content_length);
	if (content_length_count < 0 || content_length_count > PAYLOAD_LIMIT)
		return false;

	return true;
}

// Only exactly 1 Content-Length definition is accepted.
bool HeaderFieldValidator::ValidContentLength(ssize_t& content_length_count,
												string content_length) {
	if (content_length != NO_VAL) {
		// if Transfer-Encoding was also defined
		if (_status == hv_MessageChunked)
			throw BadRequestException(
				"Cannot have both Content-Length and Transfer-Encoding headers");
		// if multiple values
		else if (content_length.find(',') != string::npos)
			throw BadRequestException(
				"Cannot have multiple Content-Length values");
		else if (!ValidContentLengthValue(content_length_count, content_length))
			throw BadRequestException("Invalid Content-Length value");
		_status = hv_MessageExpected;
	}
	return true;
}
