#include "request_validator.hpp"
#include "request.hpp"

#define DEBUG 0 // TODO: REMOVE

RequestValidator::RequestValidator(NginxConfig* config,
									TargetConfig* target_config)
	:	_status(hv_Done),
		_config(config),
		_target_config(target_config) {}

RequestValidator::~RequestValidator() {}

HeaderStatus	RequestValidator::Process(Request& request) {
	if (DEBUG) cout << "RequestValidator::Process\n";
	
	if (PreConfigValidate(request)
		&& SetupConfig(_config, request)
		&& PostConfigValidate(request))
		return _status;
	return hv_Bad;
}

bool	RequestValidator::PreConfigValidate(Request& request) {
	return (ValidHost(request)
			&& ValidExpect(request)
			&& ValidContentEncoding(request.GetField("content-encoding"))
			&& ValidTransferEncoding(request));
}

int	RequestValidator::SetupConfig(NginxConfig* config,
									Request const& request) {
	string	host = request.GetTargetURI().GetHost();
	string	port = request.GetTargetURI().GetPort();
	string	target = request.GetTargetURI().GetPath(); // TODO: check if query is needed

	_target_config->Setup(config, host, port, target);
	return 1;
}

bool	RequestValidator::PostConfigValidate(Request& request) {
	return (ValidContentLength(request) && ValidMethod(request.GetMethod()));
}

void	RequestValidator::ResolveTarget(Request& request) {
	(void)request;

// 	string	target = request.GetTargetURI().GetPath();
// 	string	resolved_target_path = _target_config->GetFinalPath(target);
// 	request.SetFinalTargetPath(resolved_target_path);
}

// Only exactly 1 Host definition is accepted.
bool	RequestValidator::ValidHost(Request& request) {
	if (DEBUG) cout << "ValidHost\n";

	string	host = request.GetField("host");
	if (host == NO_VAL)
		throw BadRequestException("Host header mandatory");
	if (host.find(' ') != string::npos || host.find(',') != string::npos)
		throw BadRequestException("Multiple hosts not allowed");
	try {
		// Checks if Host value is valid path.
		// Calls on URI::SetPath that parses and validates string.
		// If success, host string is added to request target URI object.
		request.SetTargetHost(host);
	}
	catch (std::exception &e) {
		throw;
	}
	return true;
}

// Only accepts "100-continue" for Expect header.
bool	RequestValidator::ValidExpect(Request& request) {
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
bool	RequestValidator::ValidContentEncoding(string const& content_encoding) {
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
bool	RequestValidator::ValidTransferEncoding(Request& request) {
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
static void	CheckContentLengthValue(TargetConfig* target_config,
									Request& request) {
	string	content_length = request.GetField("content-length");

	// non-digit value
	if (!IsValidString(isdigit, content_length))
		throw BadRequestException("Invalid Content-Length value");

	request.content_length = std::stoll(content_length);
	request.max_body_size = MBToBytes(target_config->GetMaxBodySize());
	
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
bool	RequestValidator::ValidContentLength(Request& request) {
	if (DEBUG) cout << "ValidContentLength\n";

	string	content_length = request.GetField("content-length");

	if (content_length != NO_VAL) {
		CheckIfTransferEncodingDefined(_status);
		CheckForMultipleValues(content_length);
		CheckContentLengthValue(_target_config, request);
		CheckAllowedMethod(request.GetMethod(), request.content_length);
		if (request.content_length == 0)
			_status = hv_Done;
		else
			_status = hv_MessageExpected;
	}
	return true;
}

bool	RequestValidator::ValidMethod(string const& method) {
	if (DEBUG) cout << "ValidMethod\n";

	if (DEBUG) cout << "IsAllowedMethod returns: " <<  _target_config->IsAllowedMethod(method) << endl;
	if	(_target_config->IsAllowedMethod(method) == false)
		throw BadRequestException("Method not allowed for specified target");
	else
		return true;
}


#undef DEBUG // REMOVE