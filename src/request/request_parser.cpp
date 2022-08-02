#include "request_parser.hpp"

#define DEBUG 0 // TODO: REMOVE

// Default constructor
RequestParser::RequestParser() : StateParser(r_RequestLine), _bytes_read(0) {}

// C-string constructor
RequestParser::RequestParser(char const* buffer)
		: StateParser(r_RequestLine), _bytes_read(0) {
	Parse(buffer);
}

// Destructor
RequestParser::~RequestParser() {}

// Casts input buffer into string, resets internal counters,
// and passes string to StateParser::ParseString().
size_t	RequestParser::Parse(char const* buffer) {
	string	request(buffer);

	_bytes_read = 0;
	return ParseString(request);
}

// Retrieves next state based on current state & input.
RequestState	RequestParser::GetNextState(size_t pos) {
	static RequestState (RequestParser::*table[])(size_t pos) = {
			&RequestParser::RequestLineHandler,
			&RequestParser::HeaderFieldHandler,
			&RequestParser::HeaderDoneHandler,
			// &RequestParser::MessageBodyHandler,
			nullptr
	};

	if (DEBUG) cout << "[RP::GetNextState] pos: " << pos << " state: " << cur_state << " in [pos]: " << input[pos] << endl; // DEBUG
	return (this->*table[cur_state])(pos);
}

void	RequestParser::CheckInvalidState() const {
	if (cur_state == r_Invalid)
		throw BadRequestException("Invalid token in request");
}

bool	RequestParser::CheckDoneState() {
	return cur_state == r_Done;
}

void	RequestParser::IncrementCounter(size_t& pos) {
	pos = _bytes_read;
}

void	RequestParser::PreParseCheck() {

}

void	RequestParser::AfterParseCheck(size_t& pos) {
	if (DEBUG) {
		cout << "Parsed method: " << _request_line.method << endl; // DEBUG
		cout << "Target input: " << _request_line.target.GetInputURI() << endl; // DEBUG
		cout << "Parsed target: " << _request_line.target.GetURIDebug() << endl; // DEBUG
		cout << "Parsed version: " << _request_line.version << endl;  // DEBUG
		cout << "Parsed headers:\n";
		for (map<string,string>::iterator it = _header_fields.begin();
			it != _header_fields.end(); it++)
				cout << "\tfield: [" << it->first << "] | value: [" << it->second << "]\n";
	}
	(void)pos;
}

// Calls on RequestLineParser to parse request line, as delimited by first LF.
RequestState	RequestParser::RequestLineHandler(size_t pos) {
	if (DEBUG) cout << "[Request Line Handler] at: [" << input[pos] << "]\n";

	size_t	request_line_end = input.find_first_of('\n');
	if (request_line_end == string::npos)
		throw BadRequestException("Request line missing CRLF line break");

	string	request_line = input.substr(0, request_line_end + 1); // includes LF in string for parsing
	_bytes_read += _request_line_parser.Parse(_request_line, request_line);
	return r_HeaderField;
}

// Checks if header is ended with correct CRLF or LF sequence.
static size_t	FindFieldEnd(string const& input, size_t pos) {
	size_t	only_nls = input.find("\n\n", pos);
	size_t	crnl = input.find("\n\r\n", pos);

	if (crnl != string::npos)
		return crnl;
	else if (only_nls != string::npos)
		return only_nls;
	else
		throw BadRequestException("Header field missing line break");
}

// Calls on HeaderFieldParser to parse header fields, as delimited by empty line.
RequestState	RequestParser::HeaderFieldHandler(size_t pos) {
	if (DEBUG) cout << "[Field Handler] at: [" << input[pos] << "]\n";

	size_t	field_end = FindFieldEnd(input, pos);
	string	header_field = input.substr(pos, field_end);
	_bytes_read += _header_parser.Parse(_header_fields, header_field);
	return r_HeaderDone;
}

// Validates parsed header fields and checks if message is expected.
RequestState	RequestParser::HeaderDoneHandler(size_t pos) {
	if (DEBUG) cout << "[Header Done Handler] at pos " << pos << endl;

	// Check parsed headers if message is expected
	return r_Done;
}

string	RequestParser::GetMethod() const {
	return _request_line.method;
}

string	RequestParser::GetTarget() const {
	return _request_line.target.Get();
}

URI const&	RequestParser::GetURI() const {
	return _request_line.target;
}

string	RequestParser::GetVersion() const {
	return _request_line.version;
}

// Retrieves header field value associated with `field_name` parameter.
// If no header field with that name is found, returns macro NO_VAL, which
// expands to string "NO SUCH HEADER FIELD" (defined in request_parser.hpp).
// Example use:
//		request_parser.GetField("host")
string	RequestParser::GetField(string field_name) const {
	// Normalizes field name to lowercase for case-insensitive searching
	NormalizeString(tolower, field_name, 0);
	map<string, string>::const_iterator	found =  _header_fields.find(field_name);
	if (found == _header_fields.end())
		return NO_VAL;
	return found->second;
}

string	RequestParser::GetMessageBody() const {
	return _msg_body;
}
#undef DEBUG // REMOVE
