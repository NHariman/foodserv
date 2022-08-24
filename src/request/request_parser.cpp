#include "request_parser.hpp"
#include "chunked_parser.hpp"
#include "header_field_validator.hpp"
#include "request.hpp"

#define DEBUG 1 // TODO: REMOVE

// Default constructor // TODO: Review use/removal
RequestParser::RequestParser()
	: StateParser(r_RequestLine, r_Done), _request(NULL) {
	HeaderFieldValidator header_validator;

	_header_validator = &header_validator;
}

// Config constructor
RequestParser::RequestParser(NginxConfig *config)
		:	StateParser(r_RequestLine, r_Done),
			_config(config),
			_request(NULL) {
	HeaderFieldValidator header_validator;

	_header_validator = &header_validator;
}

// Destructor
RequestParser::~RequestParser() {}

// Casts input buffer into string, resets internal counters,
// and passes string to StateParser::ParseString().
size_t	RequestParser::Parse(Request& request, string buffer) {
	_request = &request;

	return ParseString(buffer);
}

// Retrieves next state based on current state & input.
RequestState	RequestParser::GetNextState(size_t pos) {
	static RequestState (RequestParser::*table[])() = {
			&RequestParser::RequestLineHandler,
			&RequestParser::HeaderFieldHandler,
			&RequestParser::HeaderDoneHandler,
			&RequestParser::MessageBodyHandler,
			&RequestParser::ChunkedHandler,
			nullptr
	};
	(void)pos;
	if (DEBUG) cout << "[RP::GetNextState] pos: " << pos << " state: " << cur_state << " in [pos]: " << input[pos] << endl; // DEBUG
	return (this->*table[cur_state])();
}

void	RequestParser::CheckInvalidState() const {
	if (cur_state == r_Invalid)
		throw BadRequestException("Invalid token in request");
}

bool	RequestParser::CheckDoneState() {
	return cur_state == r_Done;
}

void	RequestParser::IncrementCounter() {}

void	RequestParser::PreParseCheck() {
	cout << "RequestParser | preparse " << endl;
}

void	RequestParser::AfterParseCheck() {
	// If there are more characters after ending token, assume body
	// is present but not indicated by Content-Length header.
	if (cur_state == r_Done && pos < input.size() - 1) { // TODO: check if Content-Length has not been indicated? (truncated message)
		if (_request->GetField("Content-Length") == NO_VAL)
			throw LengthRequiredException();
	}
	if (DEBUG) {
		cout << "Parsed method: " << _request->GetMethod() << endl; // DEBUG
		cout << "Target input: " << _request->GetURI().GetInputURI() << endl; // DEBUG
		cout << "Parsed target: " << _request->GetURI().GetURIDebug() << endl; // DEBUG
		cout << "Parsed version: " << _request->GetVersion() << endl;  // DEBUG
		cout << "Parsed headers:\n";
		for (map<string,string>::iterator it = _request->_header_fields.begin();
			it != _request->_header_fields.end(); it++)
				cout << "\tfield: [" << it->first << "] | value: [" << it->second << "]\n";
		cout << "Parsed message: [" << _request->GetMessageBody() << "]\n";
	}
}

// Calls on RequestLineParser to parse request line, as delimited by first LF.
RequestState	RequestParser::RequestLineHandler() {
	if (DEBUG) cout << "[Request Line Handler] at: [" << input[pos] << "]\n";

	size_t	request_line_end = input.find_first_of('\n');
	if (request_line_end == string::npos)
		throw BadRequestException("Request line missing CRLF line break");

	string	request_line = input.substr(0, request_line_end + 1); // includes LF in string for parsing
	pos += _request_line_parser.Parse(_request->_request_line, request_line);
	// if (_header_parser.IsDone() == true)
		return r_HeaderField;
	// else
	// 	return r_RequestLine;
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
RequestState	RequestParser::HeaderFieldHandler() {
	if (DEBUG) cout << "[Field Handler] at: [" << input[pos] << "]\n";

	size_t	field_end = FindFieldEnd(input, pos); // TODO: remove?
	(void)field_end;
	// cout << "field end: " << field_end << " pos: " << pos << endl;
	// string	header_field = input.substr(pos, field_end - pos);
	string header_field = input.substr(pos);
	// cout << "Header field: len (" << header_field.length() << ") [" << header_field << "]\n";
	pos += _header_parser.Parse(_request->_header_fields, header_field);
	if (_header_parser.IsDone() == true)
		return r_HeaderDone;
	else
		return r_HeaderField;
}

// Validates parsed header fields and checks if message is expected.
RequestState	RequestParser::HeaderDoneHandler() {
	if (DEBUG) cout << "[Header Done Handler] at pos " << pos << endl;

	int ret_code = _header_validator->Process(_config, *_request);
	// cout << "Validator return: " << ret_code << endl;
	switch (ret_code) {
		case hv_Done:
			return r_Done;
		case hv_MessageExpected:
			return r_MsgBody;
		case hv_MessageChunked:
			return r_Chunked;
		default:
			return r_Invalid;
	}
}

// Called when Content-Length indicates message is expected.
RequestState	RequestParser::MessageBodyHandler() {
	if (DEBUG) cout << "[Message Body Handler] at: [" << input[pos] << "]\n";
	
	_request->_msg_body = input.substr(pos, _request->content_length);
	pos += _request->_msg_body.size();
	return r_Done;
}

RequestState	RequestParser::ChunkedHandler() {
	if (DEBUG) cout << "[Chunked Handler] at: [" << input[pos] << "]\n";

	if (input[pos]) {
		ChunkedParser parser;

		pos += parser.Parse(*_request, input.substr(pos));
		return r_Done;
	}
	else {
		pos += 1;
		return r_Chunked;
	}
}

#undef DEBUG // REMOVE
