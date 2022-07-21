#include "request_parser.hpp"

/*

HandleRequest
|_ ParseRequest
	|_ ParseRequestLine (into struct)
		|_ ParseMethod
		|_ ParseTarget
		|_ ParseHTTP
	|_ ParseHeaderField (into hash table)
		|_ ParseFieldName
		|_ ParseFieldValue
	|_ ParseReceivedforContentIndication
	if expecting message body
		|_ ParseHeaderMessage
	|_ ValidateRequest
CreateResponse
|_ 

	r_Start = 0,
	r_Method,
	r_Target,
	r_Version,
	r_Version_Done,
	r_Field,
	r_Header_Done,
	r_MsgBody,
	r_Done,
	r_Invalid
*/

/*
	Transition table for request parser
	MT = Method, URI, VR = Version, FN = FieldName, FS = FieldStart, FV = FieldValue

	// TCh       VCh       SP       WHTSP    URI       HTTP     ht       :       \n       \0
	{  MT,       x,        x,       x,       x,        x,       x,       x,       x,       x     }, // Start
	{  MT,       x,        URI,     x,       x,        x,       x,       x,       x,       x     }, // Method
	{  x,        x,        VR,      x,       URI,      x,       x,       URI,     x,       x     }, // URI
	{  x,        x,        x,       x,       x,        VR,      x,       x,       FS,      DONE  }, // Version
	{  FN,       x,        x,       x,       x,        x,       x,       x,       DONE,    x     }, // FieldStart
	{  FN,       x,        x,       x,       x,        x,       x,       FV,      x,       x     }, // FieldName
	{  x,        FV,       FV,      DONE,    x,        x,       FV,      x,       FS,      DONE  }, // FieldValue
*/

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

void	RequestParser::Parse(char const* buffer) {
	string	request(buffer);

	ParseString(request);
}

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
	if (cur_state == r_Done) {
		return true;
	}
	return false;
}

// bool	RequestParser::NotDone(size_t pos) const {
// 	return 
// }

void	RequestParser::IncrementCounter(size_t& pos) {
	pos = _bytes_read;
}

void	RequestParser::PreParseCheck() {

}

void	RequestParser::AfterParseCheck(size_t& pos) {
	// if (cur_state == r_Done && pos < input.size() - 1)
	// 	throw BadRequestException();
	cout << "Parsed method: " << _request_line.method << endl; // DEBUG
	cout << "Target input: " << _request_line.target.GetInputURI() << endl; // DEBUG
	cout << "Parsed target: " << _request_line.target.GetURIDebug() << endl; // DEBUG
	cout << "Parsed version: " << _request_line.version << endl;  // DEBUG
	cout << "Parsed headers:\n";
	for (map<string,string>::iterator it = _header_fields.begin();
		it != _header_fields.end(); it++)
			cout << "\tfield: [" << it->first << "] | value: [" << it->second << "]\n";
	(void)pos;
}

RequestState	RequestParser::RequestLineHandler(size_t pos) {
	if (DEBUG) cout << "[Request Line Handler] at: [" << input[pos] << "]\n";

	size_t	request_line_end = input.find_first_of('\n');
	if (request_line_end == string::npos)
		throw BadRequestException("Request line missing CRLF line break");
	string	request_line = input.substr(0, request_line_end + 1); // includes LF in string for parsing
	// cout << "request_line (len " << request_line.size() << "): [" << request_line << "]\n";
	_bytes_read += _request_line_parser.Parse(_request_line, request_line);
	return r_HeaderField;
}

RequestState	RequestParser::HeaderFieldHandler(size_t pos) {
	if (DEBUG) cout << "[Field Handler] at: [" << input[pos] << "]\n";

	// checks if header is not correctly ended by empty line
	size_t	field_end = input.find("\n\n", pos);
	if (field_end == string::npos)
		throw BadRequestException("Header field missing line break");

	string	header_field = input.substr(pos, field_end);
	// cout << "header (len " << header_field.size() << "): [" << header_field << "]\n";
	_bytes_read += _header_parser.Parse(_header_fields, header_field);
	return r_HeaderDone;
}

RequestState	RequestParser::HeaderDoneHandler(size_t pos) {
	if (DEBUG) cout << "[Header Done Handler] at pos " << pos << endl;

	// Check parsed headers if message is expected
	// _bytes_read += 1;
	return r_Done;
}

string	RequestParser::GetMethod() {
	return _request_line.method;
}

string	RequestParser::GetTarget() {
	return _request_line.target.Get();
}

string	RequestParser::GetVersion() {
	return _request_line.version;
}

string	RequestParser::GetHeaderFieldValue(string field_name) {
	// normalizes field name to lowercase for case-insensitive searching
	NormalizeString(tolower, field_name, 0);

	map<string, string>::iterator	found =  _header_fields.find(field_name);
	if (found == _header_fields.end())
		return NO_VAL;
	return found->second;
}

string	RequestParser::GetMessageBody() {
	return _msg_body;
}
#undef DEBUG // REMOVE