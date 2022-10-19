#include "request.hpp"
#include "request_line_parser.hpp"

// // Default constructor // TODO: Review use/removal
// Request::Request()
// 	:	HTTPMessage(),
// 		bytes_read(0),
// 		msg_bytes_read(0),
// 		max_body_size(1048576),
// 		_request_status(Status::Incomplete) {}

// Config file constructor
Request::Request(NginxConfig* config)
	:	HTTPMessage(),
		bytes_read(0),
		msg_bytes_read(0),
		max_body_size(1048576),
		_parser(config),
		_request_status(Status::Incomplete) {}

// Destructor
Request::~Request() {}

// Buffers the input string until either end of header section
// or start of message is reached.
size_t	Request::Parse(char const* buffer) {
	std::string buf(buffer);

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
		}
	}
	return bytes_read;
}

TargetConfig const&	Request::GetTargetConfig() const {
	return _target_config;
}

std::string const&	Request::GetMethod() const {
	return _method;
}

std::string const&	Request::GetTargetString() const {
	return _target.Get();
}

URI const&	Request::GetTargetURI() const{
	return _target;
}

Request::Status	Request::GetRequestStatus() const {
	return _request_status;
}

std::string	Request::GetQuery() {
	if (_method == "GET")
		return _target.GetQuery();
	else if (_method == "POST") {
		_message_body = DecodePercent(_message_body);
		return _message_body;
	}
	else
		return "";
}

void	Request::SetMethod(std::string const& method) {
	_method = method;
}

void	Request::SetRequestStatus(Status status) {
	_request_status = status;
}

void	Request::SetTarget(std::string const& target) {
	_target = target;
}

void	Request::SetTargetHost(std::string const& host) {
	_target.SetHost(host);
}

// Checks if double CRLF indicating end of header section is found
// or message stage has been reached.
bool	Request::CanParse() {
	return (_buf.find("\n\r\n") != std::string::npos
			|| _buf.find("\n\n") != std::string::npos
			|| _parser.cur_state == r_Chunked
			|| _parser.cur_state == r_MsgBody);
}

// Checks RequestParser status if it's done or if Expect header was given.
// If latter, only sends 100 (Continue) response if a message is expected
// but nothing is received yet.
void	Request::CheckStatus() {
	if (_parser.cur_state == r_Done)
		_request_status = Status::Complete;
	else if (_request_status == Status::Expect) {
		if (msg_bytes_read > 0)
			_request_status = Status::Incomplete;
		else
			SetStatusCode(100);
	}
	return ;
}
