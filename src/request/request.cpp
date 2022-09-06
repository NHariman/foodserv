#include "request.hpp"
#include "request_line_parser.hpp"

// Default constructor // TODO: Review use/removal
Request::Request()
	:	bytes_read(0),
		msg_bytes_read(0),
		content_length(-1),
		max_body_size(1048576),
		_status(Status::Incomplete),
		_status_code(0) {}

// Config file constructor
Request::Request(NginxConfig* config)
	:	bytes_read(0),
		msg_bytes_read(0),
		content_length(-1),
		max_body_size(1048576),
		_parser(config),
		_status(Status::Incomplete),
		_status_code(0) {}

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
			_status_code = e.which();
			_status = Status::Bad;
			throw;
		}
	}
	return bytes_read;
}

TargetConfig const&	Request::GetTargetConfig() const {
	return _target_config;
}

string	Request::GetMethod() const {
	return _request_line.method;
}

string	Request::GetTargetString() const {
	return _request_line.target.Get();
}

URI const&	Request::GetTargetURI() const{
	return _request_line.target;
}

string	Request::GetVersion() const {
	return _request_line.version;
}

// Retrieves header field value associated with `field_name` parameter.
// If no header field with that name is found, returns macro NO_VAL, which
// expands to string "NO SUCH HEADER FIELD" (defined in request_parser.hpp).
// Example use:
//		request_parser.GetField("host")
string	Request::GetField(string field_name) const {
	// Normalizes field name to lowercase for case-insensitive searching
	NormalizeString(tolower, field_name, 0);
	map<string, string>::const_iterator	found = _header_fields.find(field_name);
	if (found == _header_fields.end())
		return NO_VAL;
	return found->second;
}

string	Request::GetMessageBody() const {
	return _msg_body;
}

typename Request::FieldsMap const&	Request::GetFields() const {
	return _header_fields;
}

Request::Status	Request::GetStatus() const {
	return _status;
}

int	Request::GetStatusCode() const {
	return _status_code;
}

void	Request::SetStatus(Status status) {
	_status = status;
}

void	Request::SetTargetHost(string host) {
	_request_line.target.SetHost(host);
}

void	Request::SetFinalTargetPath(string target_path) {
	_request_line.target.SetPath(target_path);
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
		_status = Status::Complete;
	else if (_status == Status::Expect && msg_bytes_read > 0)
		_status = Status::Incomplete;
	return ;
}
