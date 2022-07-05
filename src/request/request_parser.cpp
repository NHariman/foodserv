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
	r_URI,
	r_Version,
	r_Key,
	r_Value,
	r_Done,
	r_Invalid
*/

// Default constructor
RequestParser::RequestParser() : _bytes_read(0) {
	
}

// Destructor
RequestParser::~RequestParser() {
	
}

void	RequestParser::Init(char const* buffer) {
	string	request(buffer);

	Parse(request);
}

RequestState	RequestParser::SetStartState() const {
	return r_Start;
}

RequestState	RequestParser::GetNextState(char c) {
	static RequestState (RequestParser::*table[7])(char req_char) = {
			&RequestParser::StartHandler,
			&RequestParser::MethodHandler,
			&RequestParser::TargetHandler,
			&RequestParser::VersionHandler,
			&RequestParser::FieldNameHandler,
			&RequestParser::FieldValueHandler,
			nullptr
	};

	return (this->*table[cur_state])(c);
}

void			RequestParser::InvalidStateCheck() const {
	if (cur_state == r_Invalid)
		throw BadRequestException();
}

bool			RequestParser::DoneStateCheck() {
	if (cur_state == r_Done) {
		return true;
	}
	return false;
}

// Checks if request is missing required LF line terminator.
void			RequestParser::PreParseCheck() const {
	if (input.find_first_of("\n") == string::npos) // recognizes single LF as linebreak for robustness
		throw BadRequestException();
}

void			RequestParser::AfterParseCheck(size_t pos) const {

}

RequestState RequestParser::StartHandler(char uri_char) {

}

RequestState RequestParser::MethodHandler(char uri_char) {

}

RequestState RequestParser::TargetHandler(char uri_char) {

}

RequestState RequestParser::VersionHandler(char uri_char) {

}

RequestState RequestParser::FieldNameHandler(char uri_char) {

}

RequestState RequestParser::FieldValueHandler(char uri_char) {

}


size_t	RequestParser::ParseRequestLine(string const& message) {
	size_t read = 0;
	size_t read_until = message.find_first_of("\n"); // recognizes single LF as linebreak for robustness

	if (read_until == string::npos)  // if no line terminator found
		throw BadRequestException();

	while (read < read_until) {
		read += ParseMethod(message);
		cout << "Parsed method: " << _request_line.method << endl; // DEBUG
		read += ParseTarget(message, read);
		cout << "Target input: " << _request_line.target.GetInputURI() << endl; // DEBUG
		cout << "Parsed target: " << _request_line.target.GetURIDebug() << endl; // DEBUG
		return read;
	}
	return read;
}

size_t	RequestParser::ParseMethod(string const& message) {
	cout << "ParseMethod\n"; // DEBUG
	
	size_t sp_pos = message.find_first_of(" ");
	string method = message.substr(0, sp_pos);

	// if method breaks grammar rules or there's more than 1 space, throw Bad Request exception
	if (method.size() == 0 || !IsValidString(IsTChar, method) || IsSpace(message[sp_pos + 1]))
		throw BadRequestException();
	// TODO: add not-implemented-method check
	_request_line.method = method;
	return sp_pos + 1;
}

size_t	RequestParser::ParseTarget(string const& message, size_t start) {
	cout << "ParseTarget\n"; // DEBUG
	
	size_t sp_pos = message.find_first_of(" ", start);
	string target = message.substr(start, sp_pos - start);

	if (IsSpace(message[sp_pos + 1])) // if there's more than 1 space
		throw BadRequestException();
	_request_line.target = target;
	return sp_pos + 1;
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

string	RequestParser::GetMessageBody() {
	return _msg_body;
}
