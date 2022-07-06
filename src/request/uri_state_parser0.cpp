#include "uri_state_parser.hpp"

RequestURIParser::RequestURIParser(URI& uri) : _uri(&uri) {}

RequestURIParser::~RequestURIParser() {}

/*
	Transition table for origin form URI states.
	PT = Path, PR = Percent, PD = PercentDone, QR = Query

	//  /        %        ?        PCh       Hex      #       \0
	{  PT,       x,       x,       x,        x,       x,       x     }, // Start
	{  PT,       PR,      QR,      PT,       PT,      x,       DONE  }, // Path
	{  x,        x,       x,       x,        PH/PD,   x,       x     }, // Percent
	{  PT/QR,    PR,      QR,      PT/QR,    PT/QR,   x/DONE,  DONE  }, // PercentDone
	{  QR,       PR,      QR,      QR,       QR,      DONE,    DONE  }, // Query

	// static URIState const uri_transitions[10][256] // REMOVE
*/

// Optional `part` argument for later parsing of host field or query field.
void	RequestURIParser::Parse(string uri_string, URIPart part) {
	_part = part;
	_uri_input = uri_string;
	if (_part == pt_Host)
		ParseHost(uri_string);
	ParsePathOriginForm(uri_string);
}

void	RequestURIParser::ParseHost(string const& uri_string) {
	(void)uri_string;
}

// Finite state machine parser that parses URI string input byte-by-byte,
// using a jump table of handler functions for each state, which sets
// the next state based on current input character.
void	RequestURIParser::ParsePathOriginForm(string const& uri_string) {
	static URIState (RequestURIParser::*uri_jumptable[6])(char uri_char) = {
			&RequestURIParser::StartHandler,
			&RequestURIParser::PathHandler,
			&RequestURIParser::QueryHandler,
			&RequestURIParser::PercentHandler,
			&RequestURIParser::PercentDoneHandler,
			nullptr
	};
	size_t i;

	if (uri_string.size() > 8190)
		throw URITooLongException();

	URIState state = u_Start;
	for (i = 0; i <= uri_string.size(); i++) {
		state = (this->*uri_jumptable[state])(uri_string[i]);
		if (state == u_Invalid)
			throw BadRequestException();
		else if (state == u_Done) {
			PushBuffertoField(_part);
			break;
		}
		_buffer += uri_string[i];
	}
	if (state == u_Done && i < uri_string.size() - 1)
		throw BadRequestException();
}

// Pushes buffer to appropriate URI field when valid ending token indicates
// transition out of current (path/query) state to next or final state.
void	RequestURIParser::PushBuffertoField(URIPart part) {
	if (part == pt_Path) {
		size_t query_start = _buffer.find_first_of("?");
		_uri->SetPath(_buffer.substr(0, query_start));
	}
	else {
		_uri->SetQuery(_buffer);
	}
	_buffer.clear();
}

// Starting state transition handler. Only accepts '/' according to origin form rules.
URIState		RequestURIParser::StartHandler(char uri_char) {
	if (uri_char == '/')
		return u_Path;
	return u_Invalid;
}

// Handles transition after '/' input indicating path section in URI.
// Always checks that no 2 consecutive '/' are given, which is only used
// by authority URI components.
URIState		RequestURIParser::PathHandler(char uri_char) {
	_part = pt_Path;
	if (DEBUG)
		cout << "PH at char [" << uri_char << "], buffer: " << _buffer << endl; // DEBUG 
	switch (uri_char) {
		case '\0':
			return u_Done;
		case '%':
			return u_Percent;
		case '?':
			return u_Query;
		case '/':
			if (_buffer.back() != '/')
				return u_Path;
		default:
			if (IsPChar(uri_char))
				return u_Path;
			else
				return u_Invalid;
	}
}

// Handles transition after '?' input indicating queries is found.
// '#' is accepted alternative to EOL signaling end of query string.
URIState		RequestURIParser::QueryHandler(char uri_char) {
	if (DEBUG)
		cout << "QH at char [" << uri_char << "], buffer: " << _buffer << endl; // DEBUG
	if (_part == pt_Path)
		PushBuffertoField(_part);
	_part = pt_Query;
	switch (uri_char) {
		case '\0': case '#':
			return u_Done;
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
URIState		RequestURIParser::PercentHandler(char uri_char) {
	if (DEBUG)
		cout << "%H at char [" << uri_char << "], buffer: " << _buffer << endl; // DEBUG 
	if (_buffer.back() == '%' && IsHexDig(uri_char))
		return u_Percent;
	else if (IsHexDig(_buffer.back()) && IsHexDig(uri_char))
		return u_Percent_Done;
	return u_Invalid;
}

// Handles transition after a valid %HH sequence.
// PChar & '/' input trigger transition to either Query or Path state
// depending on if we're at the Path or Query part of the URI.
// "return URIState(_path)" leverages equivalency between pt_Path & pt_Query values
// in URIPart enum and u_Path & Query state values in the URIState enum.
// So if we're at Path part, we return the Path state. Ditto for query.
URIState		RequestURIParser::PercentDoneHandler(char uri_char) {
	DecodePercent();
	switch (uri_char) {
		case '\0':
			return u_Done;
		case '#':
			if (_part == pt_Query)
				return u_Done;
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
}

// Called after validating percent-encoded tokens and in PercentDone state.
void	RequestURIParser::DecodePercent() {
	size_t	percent_start = _buffer.size() - 3;
	string	new_buffer = _buffer.substr(0, percent_start);
	string	hex = _buffer.substr(percent_start + 1, percent_start + 2);
	char	c = std::stoi(hex, nullptr, 16);
	new_buffer += c;
	_buffer = new_buffer;
} 