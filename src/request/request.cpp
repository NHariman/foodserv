#include "request.hpp"
#include "request_line_parser.hpp"

// Default constructor // TODO: Review use/removal
Request::Request()
	:	bytes_read(0),
		content_length(-1),
		max_body_size(1048576),
		is_complete(false) {} //,
		// _parser(NULL) {}

// Config file constructor
Request::Request(NginxConfig* config)
	:	bytes_read(0), content_length(-1), max_body_size(1048576),
		is_complete(false), _parser(config) {}

// Destructor
Request::~Request() {}

size_t	Request::Parse(char const* buffer) {
	string buf(buffer);

	_buf += buf;
	if (_buf.find("\n\r\n") != string::npos || _buf.find("\n\n") != string::npos
		|| _parser.cur_state == r_Chunked || _parser.cur_state == r_MsgBody) {
		try {
			bytes_read += _parser.Parse(*this, _buf);
			_buf.clear();
		}
		catch (std::exception &e) {
			// cout << "Parse error: " << e.what() << endl; // without this unhandled exceptions cause segfault
			throw;
		}
		if (_parser.cur_state == r_Done)
			is_complete = true;
	}
	return bytes_read;
}

string	Request::GetMethod() const {
	return _request_line.method;
}

string	Request::GetTarget() const {
	return _request_line.target.Get();
}

URI const&	Request::GetURI() const {
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

map<string, string> const&	Request::GetFields() const {
	return _header_fields;
}
