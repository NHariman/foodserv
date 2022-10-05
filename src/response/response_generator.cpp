#include "response_generator.hpp"

ResponseGenerator::ResponseGenerator() {}

ResponseGenerator::~ResponseGenerator() {}

void	ResponseGenerator::FormResponse(Response& response, Request* request) {
	_response = &response;
	_request = request;

	SetStatusLine();
	if (_response->GetStatusCode() != 100)
		SetHeaders();
	_response->SetComplete();
}

void	ResponseGenerator::SetStatusLine() {
	_response->SetHTTPVersion("HTTP/1.1");
	if (_response->GetStatusCode() == 0)
		_response->SetStatusCode(_request->GetStatusCode());
	_response->SetReasonPhrase(GetReasonPhrase(_response->GetStatusCode()));
}

void	ResponseGenerator::SetHeaders() {
	SetAllow();
	SetConnection();
	SetContentLength();
	SetContentType();
	SetDate();
	SetLocation();
	SetServer();
}

// Allow is only set if returning a 405: Method Not Allowed error.
void	ResponseGenerator::SetAllow() {
	if (_response->GetStatusCode() == 405)
		_response->SetHeaderField("Allow", GetAllowedMethodsString());
}

// Connection: close is always sent unless it's a 100: Continue _response->
void	ResponseGenerator::SetConnection() {
	_response->SetHeaderField("Connection", "close");
}

void	ResponseGenerator::SetContentLength() {
	std::istream* body_stream = _response->GetBodyStream();
	if (body_stream != NULL
			&& _response->GetField("Content-Length") == NO_VAL) {
		body_stream->seekg(0, std::ios_base::end); // move cursor to end of stream
		std::streampos	size = body_stream->tellg(); // get position of cursor
		_response->SetHeaderField("Content-Length", std::to_string(size));
		body_stream->seekg(0); // restore cursor to beginning
	}
}

void	ResponseGenerator::SetContentType() {
	// check if there is payload & type not already set
	if (_response->GetBodyStream() != NULL
			&& _response->GetField("Content-Type") == NO_VAL) {
		size_t	extension_start = _response->GetResolvedPath().find_last_of(".");
		std::string	type;

		type = GetType(_response->GetResolvedPath().substr(extension_start + 1));
		if (type.empty()) // if no extension or unknown extension
			type = "application/octet-stream";
		_response->SetHeaderField("Content-Type", type);
	}
}

void	ResponseGenerator::SetDate() {
	char	buf[100];
	time_t	now = time(0);
	struct tm	tm = *gmtime(&now);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %Z", &tm);

	_response->SetHeaderField("Date", std::string(buf));
}

// Location only set if request is redirected or a POST request is successfully executed (201 created).
void	ResponseGenerator::SetLocation() {
	int status_code = _response->GetStatusCode();
	if (IsRedirectCode(status_code))
		_response->SetHeaderField("Location", _response->GetResolvedPath());
	else if (status_code == 201)
		_response->SetHeaderField("Location", _request->GetTargetString());
}

void	ResponseGenerator::SetServer() {
	_response->SetHeaderField("Server", "foodserv/1.0");
}

// Used by SetAllow to set header value to comma-separated list of allowed methods.
std::string	ResponseGenerator::GetAllowedMethodsString() {
	std::vector<std::string> methods_vec = _request->GetTargetConfig().GetAllowedMethods();
	std::string	methods_str;

	for (auto it = methods_vec.begin(); it != methods_vec.end(); it++) {
		if (!methods_str.empty())
			methods_str += ", ";
		methods_str += *it;
	}
	return methods_str;
}
