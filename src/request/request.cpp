#include "request.hpp"

// Default constructor // TODO: Review use/removal
Request::Request() : bytes_read(0), content_length(-1) {}

// C-string constructor
Request::Request(NginxConfig* config, char const* buffer)
		: bytes_read(0), content_length(-1) {
	RequestParser	parser(config);

	bytes_read = parser.Parse(*this, buffer);
}

// Destructor
Request::~Request() {}

string	Request::GetMethod() const {
	return request_line.method;
}

string	Request::GetTarget() const {
	return request_line.target.Get();
}

URI const&	Request::GetURI() const {
	return request_line.target;
}

string	Request::GetVersion() const {
	return request_line.version;
}

// Retrieves header field value associated with `field_name` parameter.
// If no header field with that name is found, returns macro NO_VAL, which
// expands to string "NO SUCH HEADER FIELD" (defined in request_parser.hpp).
// Example use:
//		request_parser.GetField("host")
string	Request::GetField(string field_name) const {
	// Normalizes field name to lowercase for case-insensitive searching
	NormalizeString(tolower, field_name, 0);
	map<string, string>::const_iterator	found =  header_fields.find(field_name);
	if (found == header_fields.end())
		return NO_VAL;
	return found->second;
}

string	Request::GetMessageBody() const {
	return msg_body;
}