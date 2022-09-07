#include "request_target_parser.hpp"

#define DEBUG 0 // TODO: REMOVE
/*
	Transition table for origin form URI states.
	PT = Path, PR = Percent, PD = PercentDone, QR = Query, ✓ = Done

		/		%		?		PCh		Hex		#		\0
	{  PT,		x,		x,		x,		x,		x,		x	}, // Start
	{  PT,		PR,		QR,		PT,		PT,		x,		✓	}, // Path
	{  QR,		PR,		QR,		QR,		QR,		✓,		✓	}, // Query
	{  x,		x,		x,		x,		PH/PD,	x,		x	}, // Percent
	{  PT/QR,	PR,		QR,		PT/QR,	PT/QR,	x/✓,	✓	}, // PercentDone
*/

// Default constructor
RequestTargetParser::RequestTargetParser()
	: AStateParser(u_Start, u_Done), _uri(NULL), _part(URI::Part::Invalid) {}

// Destructor
RequestTargetParser::~RequestTargetParser() {}

// Initializes pointer to URI object, resets internal counters, and
// passed input string to parent class AStateParser::ParseString().
size_t	RequestTargetParser::Parse(URI& uri, string const& input) {
	_uri = &uri;
	_part = URI::Part::Path;
	return ParseString(input);
}

// Retrieves next state based on current state & character.
URIState	RequestTargetParser::GetNextState(size_t pos) {
	static 	URIState (RequestTargetParser::*table[])(char uri_char) = {
			&RequestTargetParser::StartHandler,
			&RequestTargetParser::PathHandler,
			&RequestTargetParser::QueryHandler,
			&RequestTargetParser::PercentHandler,
			&RequestTargetParser::PercentDoneHandler,
			nullptr
	};
	if (DEBUG) cout << "[RTP::GetNextState] pos: " << pos << " state: " << cur_state << " in [pos]: " << input[pos] << endl; // DEBUG
	skip_char = false;
	return (this->*table[cur_state])(input[pos]);
}

void	RequestTargetParser::CheckInvalidState() const {
	if (cur_state == u_Invalid)
		throw BadRequestException("Invalid token in request target: \"" + buffer + "\"");
}

// Checks if URI string is greater than 8kb (limit of most web servers)
void	RequestTargetParser::PreParseCheck() {
	if (input.size() > 8192)
		throw URITooLongException();
}

// Checks if there's illegal characters after terminating char.
void	RequestTargetParser::AfterParseCheck() {
	if (cur_state == u_Done && pos < input.size() - 1)
		throw BadRequestException("Extra characters after terminating token in request target");
}

// Starting state transition handler. Only accepts '/' according to origin form rules.
URIState		RequestTargetParser::StartHandler(char uri_char) {
	if (DEBUG) cout << "[StartHandler] at: [" << uri_char << "]\n";

	if (uri_char == '/')
		return u_Path;
	return u_Invalid;
}

// Handles transition after '/' input indicating path section in URI.
// Always checks that no 2 consecutive '/' are given, which is only used
// by authority URI components.
URIState		RequestTargetParser::PathHandler(char uri_char) {
	if (DEBUG) cout << "[PathHandler] at: [" << uri_char << "]\n";

	_part = URI::Part::Path;
	switch (uri_char) {
		case '\0':
			return PushBuffertoField(u_Done);
		case '%':
			return u_Percent;
		case '?':
			return PushBuffertoField(u_Query);
		case '/':
			if (!PrecededBy(buffer, '/'))
				return u_Path;
			break;
		default:
			if (IsPChar(uri_char))
				return u_Path;
			else
				return u_Invalid;
	}
	return u_Invalid;
}

// Handles transition after '?' input indicating queries is found.
// '#' is accepted alternative to EOL signaling end of query string.
URIState		RequestTargetParser::QueryHandler(char uri_char) {
	if (DEBUG) cout << "[QueryHandler] at: [" << uri_char << "]\n";

	_part = URI::Part::Query;
	switch (uri_char) {
		case '\0': case '#':
			return PushBuffertoField(u_Done);
		case '%':
			return u_Percent;
		case '/': case '?':
			return u_Query;
		default:
			if (IsPChar(uri_char))
				return u_Query;
			else
				return u_Invalid;
	}
}

// Handles transition after percent-encoding has been found (% input).
// Checks if subsequent 2 characters are valid hexadecimal digits.
URIState		RequestTargetParser::PercentHandler(char uri_char) {
	if (DEBUG) cout << "[PercentHandler] at: [" << uri_char << "]\n";

	if (PrecededBy(buffer, '%') && IsHexDig(uri_char))
		return u_Percent;
	else if (IsHexDig(buffer.back()) && IsHexDig(uri_char))
		return u_Percent_Done;
	return u_Invalid;
}

// Handles transition after a valid %HH sequence.
// PChar & '/' input trigger transition to either Query or Path state
// depending on if we're at the Path or Query part of the URI.
// "return URIState(_path)" leverages equivalency between pt_Path & pt_Query values
// in URIPart enum and u_Path & Query state values in the URIState enum.
// So if we're at Path part, we return the Path state. Ditto for Query.
URIState		RequestTargetParser::PercentDoneHandler(char uri_char) {
	if (DEBUG) cout << "[PercentDoneHandler] at: [" << uri_char << "]\n";

	NormalizeString(toupper, buffer, buffer.size() - 2);
	buffer = DecodePercent(buffer);
	switch (uri_char) {
		case '\0':
			return PushBuffertoField(u_Done);
		case '#':
			if (_part == URI::Part::Query)
				return PushBuffertoField(u_Done);
			break;
		case '%':
			return u_Percent;
		case '?':
			return u_Query;
		case '/':
			return URIState(_part); // pt_Path == u_Path; pt_Query == u_Query
		default:
			if (IsPChar(uri_char))
				return URIState(_part);
			else
				return u_Invalid;
	}
	return u_Invalid;
}

// Pushes buffer to appropriate URI field when valid ending token indicates
// transition out of current (path/query) state to next or final state.
// `skip` is optional argument that defaults to TRUE.
URIState	RequestTargetParser::PushBuffertoField(URIState next_state, bool skip) {
	if (_part == URI::Part::Path) {
		size_t query_start = buffer.find_first_of("?");
		_uri->_path = buffer.substr(0, query_start);
	}
	else
		_uri->_query = buffer;
	buffer.clear();
	skip_char = skip;
	return next_state;
}

#undef DEBUG // REMOVE