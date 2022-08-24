#include "request_line_parser.hpp"

// Default constructor
RequestLineParser::RequestLineParser()
	: StateParser(l_Start, l_Done) {}

// Destructor
RequestLineParser::~RequestLineParser() {}

// Initializes pointer to RequestLine struct, resets internal counters,
// and passes input string to parent class StateParser::ParseString().
size_t	RequestLineParser::Parse(RequestLine& request_line, string const& input) {
	pos += 0;
	_request_line = &request_line;
	return ParseString(input);
}

// Retrieves next state based on current state & input.
RequestLineState	RequestLineParser::GetNextState(size_t pos) {
	static 	RequestLineState (RequestLineParser::*table[])() = {
			&RequestLineParser::StartHandler,
			&RequestLineParser::MethodHandler,
			&RequestLineParser::TargetHandler,
			&RequestLineParser::VersionHandler,
			&RequestLineParser::VersionEndHandler,
			nullptr
	};
	(void)pos;
	return (this->*table[cur_state])();
}

void	RequestLineParser::CheckInvalidState() const {
	if (cur_state == l_Invalid)
		throw BadRequestException("Invalid token in request line: \"" + buffer + "\"");
}

bool	RequestLineParser::CheckDoneState() {
	return (cur_state == l_Done);
}

// Counter is incremented within Handler functions instead of here.
void	RequestLineParser::IncrementCounter() {}

// Checks if start is a valid TChar (as stated by RFC ABNF rules).
// Or if EOL is found (VersionEndHandler loops back to this function
// for the purposes of returning accurate bytes_read count). 
RequestLineState	RequestLineParser::StartHandler() {
	if (input[pos] == '\0' && pos != 0)
		return l_Done;
	if (IsTChar((int)input[pos]))
		return l_Method;
	return l_Invalid;
}

// Checks input string for first space-delimited string and checks it against
// vector of accepted method strings. If it's not in the list, throws NotImplementedException.
// Otherwise saves string and increments `bytes_read`.
RequestLineState	RequestLineParser::MethodHandler() {
	static vector<string>	methods = { "GET", "POST", "DELETE" };

	size_t	method_end = GetEndPos(input, ' ', pos);
	
	// if required space ending not found
	if (method_end == pos)
		throw BadRequestException("Request method missing single space delimiter");

	string	method = input.substr(pos, method_end);
	if (find(methods.begin(), methods.end(), method) == methods.end())
		throw NotImplementedException();
	_request_line->method = method;
	pos += method_end + 1;
	return l_Target;
}

// Validates request target through URI::Parse().
RequestLineState	RequestLineParser::TargetHandler() {
	size_t	target_end = GetEndPos(input, ' ', pos);
	
	// if required space ending not found
	if (target_end == pos) 
		throw BadRequestException("Request target missing single space delimiter");

	_request_line->target = input.substr(pos, target_end); // calls on RequestTargetParser
	pos += target_end + 1;
	return l_Version;
}

// Checks if HTTP version is valid (only 1.1 is accepted).
RequestLineState	RequestLineParser::VersionHandler() {
	size_t	version_end = GetCRLFPos(input, pos);
	string	version = input.substr(pos, version_end);

	if (version.front() != 'H' || !isdigit(version.back())) {
		buffer = version;
		skip_char = true;
		return l_Invalid;
	}
	if (version != "HTTP/1.1")
		throw HTTPVersionNotSupportedException();
	_request_line->version = version;
	pos += version_end;
	return l_VersionEnd;
}

// Checks the number of line break tokens to increment pos
// (CRLF and LF are accepted). Loops back to Start so line breaks are counted.
RequestLineState	RequestLineParser::VersionEndHandler() {
	if (input.substr(pos) == "\r\n" || input.substr(pos) == "\n")
		pos += (input.find("\n") + 1) - pos;
	else
		throw BadRequestException("Request line missing line break");
	return l_Start;
}

// Returns position of `to_find` within string `s` in terms of its distance from
// `start`, so value can be used immediately with `substr()`, skipping arithmetic.
// If no such character is found in string, returns `start`;
size_t	RequestLineParser::GetEndPos(string const& s, char to_find, size_t start) {
	size_t	end = s.find_first_of(to_find, start);
	if (end == string::npos || end == start)
		return start;
	return end - start;
}

size_t	RequestLineParser::GetCRLFPos(string const& input, size_t pos) {
	size_t	nl_pos = GetEndPos(input, '\n', pos);
	size_t	cr_pos = GetEndPos(input, '\r', pos);

	if (nl_pos == pos)
		throw BadRequestException("Request line missing line break");
	
	// if \r is found and precedes \n
	if (cr_pos != pos && (nl_pos - cr_pos == 1))
		return cr_pos;
	return nl_pos;
}
