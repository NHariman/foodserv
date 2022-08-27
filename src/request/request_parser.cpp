#include "request_parser.hpp"

#define DEBUG 0 // TODO: REMOVE

// Default constructor
RequestParser::RequestParser()
	: StateParser(r_RequestLine), _request(NULL), _bytes_read(0) {
	HeaderFieldValidator header_validator;

	_header_validator = &header_validator;
}

// Destructor
RequestParser::~RequestParser() {}

// Casts input buffer into string, resets internal counters,
// and passes string to StateParser::ParseString().
size_t	RequestParser::Parse(Request& request, char const* buffer) {
	string	request_string(buffer);

	_request = &request;
	_bytes_read = 0;
	return ParseString(request_string);
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
		cout << "Parsed method: " << _request->GetMethod() << endl; // DEBUG
		cout << "Target input: " << _request->GetURI().GetInputURI() << endl; // DEBUG
		cout << "Parsed target: " << _request->GetURI().GetURIDebug() << endl; // DEBUG
		cout << "Parsed version: " << _request->GetVersion() << endl;  // DEBUG
		cout << "Parsed headers:\n";
		for (map<string,string>::iterator it = _request->header_fields.begin();
			it != _request->header_fields.end(); it++)
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
	_bytes_read += _request_line_parser.Parse(_request->request_line, request_line);
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
	_bytes_read += _header_parser.Parse(_request->header_fields, header_field);
	return r_HeaderDone;
}

// Validates parsed header fields and checks if message is expected.
RequestState	RequestParser::HeaderDoneHandler(size_t pos) {
	if (DEBUG) cout << "[Header Done Handler] at pos " << pos << endl;

	int ret_code = _header_validator->Process(*_request);
	switch (ret_code) {
		case hv_OK:
			return r_Done;
		case hv_MessageExpected:
			return r_MsgBody;
		case hv_MessageChunked:
			return r_Chunked;
		default:
			return r_Invalid;
	}
}

#undef DEBUG // REMOVE
