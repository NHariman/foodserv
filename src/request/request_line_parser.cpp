#include "request_line_parser.hpp"
#define DEBUG 0 // TODO: REMOVE
RequestLineParser::RequestLineParser() : _increment(0) {}

RequestLineParser::~RequestLineParser() {}

size_t	RequestLineParser::Parse(RequestLine& request_line, string const& input) {
	_request_line = &request_line;
	return ParseString(input);
}

RequestLineState	RequestLineParser::SetStartState() const {
	return l_Start;
}

RequestLineState	RequestLineParser::GetNextState(size_t pos) {
	static 	RequestLineState (RequestLineParser::*table[])(size_t pos) = {
			&RequestLineParser::StartHandler,
			&RequestLineParser::MethodHandler,
			&RequestLineParser::TargetHandler,
			&RequestLineParser::VersionHandler,
			&RequestLineParser::VersionEndHandler,
			nullptr
	};
	if (DEBUG) cout << "[RL::GetNextState] pos: " << pos << " state: " << cur_state << " in [pos]: " << input[pos] << endl; // DEBUG
	return (this->*table[cur_state])(pos);
}

void	RequestLineParser::CheckInvalidState() const {
	if (cur_state == l_Invalid)
		throw BadRequestException();
}

bool	RequestLineParser::CheckDoneState() {
	return (cur_state == l_Done);
}

void	RequestLineParser::IncrementCounter(size_t& pos) {
	pos += _increment;
}

void	RequestLineParser::AfterParseCheck(size_t& pos) {
	pos += _increment;
}

// Checks if start is a valid TChar (as stated by RFC ABNF rules).
RequestLineState	RequestLineParser::StartHandler(size_t pos) {
	if (DEBUG) cout << "[StartHandler] at: " << input[pos] << endl;
	if (IsTChar(input[pos]))
		return l_Method;
	return l_Invalid;
}

// Checks input string for first space-delimited string and checks it against
// vector of accepted method strings. If it's not in the list, throws NotImplementedException.
// Otherwise saves string and increments `bytes_read`.
RequestLineState	RequestLineParser::MethodHandler(size_t pos) {
	if (DEBUG) cout << "[MethodHandler] at: " << input[pos] << endl;;
	static vector<string>	methods = { "GET", "POST", "DELETE" };

	size_t	method_end = GetEndPos(input, ' ', pos);
	if (method_end == pos) // if required space ending not found
		throw BadRequestException();

	string	method = input.substr(pos, method_end);
	if (find(methods.begin(), methods.end(), method) == methods.end())
		throw NotImplementedException();
	_request_line->method = method;
	_increment = method_end + 1;
	return l_Target;
}

// Validates request target through URI::Parse().
RequestLineState	RequestLineParser::TargetHandler(size_t pos) {
	if (DEBUG) cout << "[TargetHandler] at: " << input[pos] << endl;

	size_t	target_end = GetEndPos(input, ' ', pos);
	if (target_end == pos) // if required space ending not found
		throw BadRequestException();
	_request_line->target = input.substr(pos, target_end); // calls on RequestTargetParser
	_increment = target_end + 1;
	return l_Version;
}

// Checks if HTTP version is valid (only 1.1 is accepted).
RequestLineState	RequestLineParser::VersionHandler(size_t pos) {
	if (DEBUG) cout << "[VersionHandler] at: " << input[pos] << endl;

	size_t	version_end = GetCRLFPos(input, pos);
	string	version = input.substr(pos, version_end);

	if (version.front() != 'H' || !isdigit(version.back()))
		throw BadRequestException();
	if (version != "HTTP/1.1")
		throw HTTPVersionNotSupportedException();
	_request_line->version = version;
	_increment = version_end;
	return l_VersionEnd;
}

RequestLineState	RequestLineParser::VersionEndHandler(size_t pos) {
	if (DEBUG) cout << "[VersionEndHandler] at: " << input[pos] << endl;

	_increment = ValidLineBreaks(input, pos);
	if (_increment == 0)
		return l_Invalid;
	return l_Done;
}

// Returns position of `to_find` within string `s` in terms of its distance from
// `start`, so value can be used immediately with `substr()`, skipping arithmetic.
// If no such character is found in string, returns `start`;
size_t	RequestLineParser::GetEndPos(string s, char to_find, size_t start) { // TODO: remove parameters?
	size_t	end = s.find_first_of(to_find, start);
	if (end == string::npos || end == start)
		return start;
	return end - start;
}

size_t	RequestLineParser::GetCRLFPos(string const& input, size_t pos) { // TODO: remove parameters?
	size_t	nl_pos = GetEndPos(input, '\n', pos);
	size_t	cr_pos = GetEndPos(input, '\r', pos);

	if (nl_pos == pos)
		throw BadRequestException();
	if (cr_pos != pos && (nl_pos - cr_pos == 1)) // if \r is found and precedes \n
		return cr_pos;
	return nl_pos;
}

// Used by VersionDoneHandler and FieldDoneHandler to check for
// valid line breaks (CRLF or LF as specified by RFC 7230).
size_t	RequestLineParser::ValidLineBreaks(string input, size_t pos) { // TODO: remove parameters?
	if (input[pos] == '\r' && input[pos + 1] == '\n')
		return 2;
	else if (input[pos] == '\n')
		return 1;
	else
		return 0;
}


#undef DEBUG // REMOVE