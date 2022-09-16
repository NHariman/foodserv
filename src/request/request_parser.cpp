#include "request_parser.hpp"
#include "request_validator.hpp"
#include "request.hpp"

#define DEBUG 0 // TODO: REMOVE

// Default constructor // TODO: Review use/removal
RequestParser::RequestParser()
	: AStateParser(r_RequestLine, r_Done), _config(NULL), _request(NULL) {}

// Config constructor
RequestParser::RequestParser(NginxConfig *config)
		:	AStateParser(r_RequestLine, r_Done),
			_config(config),
			_request(NULL) {}

// Destructor
RequestParser::~RequestParser() {}

// Casts input buffer into string, resets internal counters,
// and passes string to AStateParser::ParseString().
size_t	RequestParser::Parse(Request& request, string const& buffer) {
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

void	RequestParser::IncrementCounter() {}

void	RequestParser::PreParseCheck() {
	if (DEBUG) cout << "\nRequestParser | preparse " << endl;
}

void	RequestParser::AfterParseCheck() {
	// If there are more characters after ending token, assume body
	// is present but not indicated by Content-Length header.
	if (cur_state == r_Done && pos < input.size() - 1) { // TODO: check if Content-Length has not been indicated? (truncated message)
		if (_request->GetField("Content-Length") == NO_VAL)
			throw LengthRequiredException();
	}
	if (DEBUG) {
		DebugPrint();
	}
}

// Calls on RequestLineParser to parse request line, as delimited by first LF.
RequestState	RequestParser::RequestLineHandler() {
	if (DEBUG) cout << "[Request Line Handler] at: [" << input[pos] << "]\n";

	size_t	request_line_end = input.find_first_of('\n');
	if (request_line_end == string::npos)
		throw BadRequestException("Request line missing CRLF line break");

	string	request_line = input.substr(0, request_line_end + 1); // includes LF in string for parsing
	pos += _request_line_parser.Parse(*_request, request_line);
	// pos += _request_line_parser.Parse(_request->_request_line, request_line);
	return r_HeaderField;
}

// Calls on HeaderFieldParser to parse header fields.
RequestState	RequestParser::HeaderFieldHandler() {
	if (DEBUG) cout << "[Field Handler] at: [" << input[pos] << "]\n";

	string header_field = input.substr(pos);
	// cout << "Header field: len (" << header_field.length() << ") [" << header_field << "]\n";
	pos += _header_parser.Parse(*_request, header_field);
	if (_header_parser.IsDone() == true) {
		if (DEBUG) cout << "--- Header Field Parsing complete. ---\n";
		return r_HeaderDone;
	}
	else
		return r_HeaderField;
}

// Validates parsed header fields and checks if message is expected.
RequestState	RequestParser::HeaderDoneHandler() {
	if (DEBUG) cout << "[Header Done Handler] at pos " << pos << endl;

	// allocated on stack because we don't need to remember the return
	RequestValidator	validator(_config, &(_request->_target_config));
	int					status;

	status = validator.Process(*_request);
	switch (status) {
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
	
	// _request->_msg_body += input.substr(pos, _request->content_length);
	string	new_message = _request->GetMessageBody()
		+ input.substr(pos, _request->GetContentLength());
	_request->SetMessageBody(new_message);

	size_t	msg_size = _request->GetMessageBody().size();
	pos += msg_size;
	_request->msg_bytes_read = msg_size;
	if (msg_size == _request->GetContentLength())
		return r_Done;
	else {
		pos += 1;
		return r_MsgBody;
	}
}

// Called when Transfer-Encoding indicates chunked message is expected.
RequestState	RequestParser::ChunkedHandler() {
	if (DEBUG) cout << "[Chunked Handler] at: [" << input[pos]
		<< "], len of input: " << input.substr(pos).length() << "\n";

	size_t bytes_read = _chunked_parser.Parse(*_request, input.substr(pos));
	if (input[pos])
		_request->msg_bytes_read += bytes_read;
	pos += bytes_read;
	if (_chunked_parser.IsDone() == true) {
		if (DEBUG) cout << "--- Chunked Parsing complete. ---\n";
		HandleEndOfChunkedMessage();
		return r_Done;
	}
	else
		return r_Chunked;
}

// Assigns Content-Length once chunked message transfer is complete,
// and removes chunked transfer coding-related header fields as
// indicated by RFC 7230 4.1.3.
void	RequestParser::HandleEndOfChunkedMessage() {
	_request->SetContentLength(_request->GetMessageBody().size());
	_request->RemoveField("transfer-encoding");
	_request->RemoveField("trailer");
}

void	RequestParser::DebugPrint() {
	cout << "Parsed method: " << _request->GetMethod() << endl;
	cout << "Target input: " << _request->GetTargetURI().GetInputURI() << endl;
	cout << "Parsed target: " << _request->GetTargetURI().GetURIDebug() << endl;
	cout << "Parsed version: " << _request->GetHTTPVersion() << endl;
	cout << "Parsed headers:\n";
	for (map<string,string>::const_iterator it = _request->GetFields().begin();
		it != _request->GetFields().end(); it++)
			cout << "\tfield: [" << it->first << "] | value: [" << it->second << "]\n";
	cout << "Parsed message: [" << _request->GetMessageBody() << "]\n";
}

#undef DEBUG // REMOVE
