#include "header_field_validator.hpp"

HeaderFieldValidator::HeaderFieldValidator() : _status(hv_Bad) {
}

HeaderFieldValidator::~HeaderFieldValidator() {}

HeaderStatus	HeaderFieldValidator::Process(Request const& request) {
	if (ValidHost(request.GetField("host"))
			&& ValidTransferEncoding(request.GetField("transfer-encoding"))
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidContentLength(request.GetField("content-length"))
			&& ValidExpect(request.GetField("expect")))
		return _status;
}

bool HeaderFieldValidator::ValidHost(string host) {
	try {
		URIHostParser	parser;
		string			host_parsed;

		parser.Parse(host_parsed, host);
	}
	catch (...) {
		throw;
	}
	return true;
}

bool HeaderFieldValidator::ValidTransferEncoding(string transfer_encoding) {
	if (transfer_encoding != NO_VAL && transfer_encoding != "chunked")
		throw NotImplementedException();
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

bool HeaderFieldValidator::ValidContentLength(string content_length) {
	
}

// Only accepts "100-continue" for Expect header.
bool HeaderFieldValidator::ValidExpect(string expect) {
	if (expect != NO_VAL && expect != "100-continue")
		throw ExpectationFailedTypeException();
	else
		return true;
}
