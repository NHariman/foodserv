#include "request.hpp"
#include "request_line_parser.hpp"

// Default constructor // TODO: Review use/removal
Request::Request()
	:	AHTTPMessage(),
		bytes_read(0),
		msg_bytes_read(0),
		content_length(-1),
		max_body_size(1048576),
		_request_status(Status::Incomplete) {}

// Config file constructor
Request::Request(NginxConfig* config)
	:	AHTTPMessage(),
		bytes_read(0),
		msg_bytes_read(0),
		content_length(-1),
		max_body_size(1048576),
		_parser(config),
		_request_status(Status::Incomplete) {}

// Destructor
Request::~Request() {}

// Buffers the input string until either end of header section
// or start of message is reached.
size_t	Request::Parse(char const* buffer) {
	string buf(buffer);

	_buf += buf;
	if (CanParse()) {
		try {
			bytes_read += _parser.Parse(*this, _buf);
			_buf.clear();
			CheckStatus();
		}
		catch (http::exception &e) {
			SetStatusCode(e.which());
			_request_status = Status::Bad;
			throw;
		}
	}
	return bytes_read;
}

TargetConfig const&	Request::GetTargetConfig() const {
	return _target_config;
}

string const&	Request::GetMethod() const {
	return _method;
}

string const&	Request::GetTargetString() const {
	return _target.Get();
}

URI const&	Request::GetTargetURI() const{
	return _target;
}

Request::Status	Request::GetRequestStatus() const {
	return _request_status;
}

void	Request::SetMethod(string const& method) {
	_method = method;
}

void	Request::SetRequestStatus(Status status) {
	_request_status = status;
}

void	Request::SetTarget(string const& target) {
	_target = target;
}

void	Request::SetTargetHost(string const& host) {
	_target.SetHost(host);
}

void	Request::SetResolvedTargetPath(string const& target_path) {
	_target.SetPath(target_path);
}

// Checks if double CRLF indicating end of header section is found
// or message stage has been reached.
bool	Request::CanParse() {
	return (_buf.find("\n\r\n") != string::npos
			|| _buf.find("\n\n") != string::npos
			|| _parser.cur_state == r_Chunked
			|| _parser.cur_state == r_MsgBody);
}

// Checks RequestParser status if it's done or if Expect header was given.
// If latter, only sends 100 (Continue) response if a message is expected
// but nothing is received yet.
void	Request::CheckStatus() {
	if (_parser.cur_state == r_Done)
		_request_status = Status::Complete;
	else if (_request_status == Status::Expect && msg_bytes_read > 0)
		_request_status = Status::Incomplete;
	return ;
}
