#include "request_target_parser.hpp"

#define DEBUG 0 // REMOVE

RequestTargetParser::RequestTargetParser() {}

RequestTargetParser::~RequestTargetParser() {}

/*
	Transition table for origin form URI states.
	PT = Path, PR = Percent, PD = PercentDone, QR = Query

	//  /        %        ?        PCh       Hex      #       \0
	{  PT,       x,       x,       x,        x,       x,       x     }, // Start
	{  PT,       PR,      QR,      PT,       PT,      x,       DONE  }, // Path
	{  x,        x,       x,       x,        PH/PD,   x,       x     }, // Percent
	{  PT/QR,    PR,      QR,      PT/QR,    PT/QR,   x/DONE,  DONE  }, // PercentDone
	{  QR,       PR,      QR,      QR,       QR,      DONE,    DONE  }, // Query
*/

void	RequestTargetParser::Parse(URI& uri, string const& uri_string) {
	_uri = &uri;
	_part = pt_Path;
	// if (_part == pt_Host)
	// 	ParseHost(uri_string);
	ParseString(uri_string);
}

// void	RequestTargetParser::ParseHost(string const& uri_string) {
// 	(void)uri_string;
// }

URIState	RequestTargetParser::SetStartState() const {
	return u_Start;
}

URIState	RequestTargetParser::GetNextState(size_t pos) {
	static 	URIState (RequestTargetParser::*table[6])(char uri_char) = {
			&RequestTargetParser::StartHandler,
			&RequestTargetParser::PathHandler,
			&RequestTargetParser::QueryHandler,
			&RequestTargetParser::PercentHandler,
			&RequestTargetParser::PercentDoneHandler,
			nullptr
	};

	return (this->*table[cur_state])(input[pos]);
}

void	RequestTargetParser::InvalidStateCheck() const {
	if (cur_state == u_Invalid)
		throw BadRequestException();
}

// If terminating state is indicated, pushes parsed string 
// into appropriate URI field (as indicated by _part) and stops loop.
bool	RequestTargetParser::DoneStateCheck() {
	if (cur_state == u_Done) {
		PushBuffertoField(_part);
		return true;
	}
	return false;
}

// Checks if URI string is greater than 8kb (limit of most web servers)
void	RequestTargetParser::PreParseCheck() {
	if (input.size() > 8192)
		throw URITooLongException();
}

// Checks if there's illegal characters after terminating char.
void	RequestTargetParser::AfterParseCheck(size_t pos) {
	if (cur_state == u_Done && pos < input.size() - 1)
		throw BadRequestException();
}

// Pushes buffer to appropriate URI field when valid ending token indicates
// transition out of current (path/query) state to next or final state.
void	RequestTargetParser::PushBuffertoField(URIPart part) {
	if (part == pt_Path) {
		size_t query_start = buffer.find_first_of("?");
		_uri->SetPath(buffer.substr(0, query_start));
	}
	else {
		_uri->SetQuery(buffer);
	}
	buffer.clear();
}

// Starting state transition handler. Only accepts '/' according to origin form rules.
URIState		RequestTargetParser::StartHandler(char uri_char) {
	if (uri_char == '/')
		return u_Path;
	return u_Invalid;
}

// Handles transition after '/' input indicating path section in URI.
// Always checks that no 2 consecutive '/' are given, which is only used
// by authority URI components.
URIState		RequestTargetParser::PathHandler(char uri_char) {
	_part = pt_Path;
	if (DEBUG)
		cout << "PH at char [" << uri_char << "], buffer: " << buffer << endl; // DEBUG 
	switch (uri_char) {
		case '\0':
			return u_Done;
		case '%':
			return u_Percent;
		case '?':
			return u_Query;
		case '/':
			if (buffer.back() != '/')
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
URIState		RequestTargetParser::QueryHandler(char uri_char) {
	if (DEBUG)
		cout << "QH at char [" << uri_char << "], buffer: " << buffer << endl; // DEBUG

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
URIState		RequestTargetParser::PercentHandler(char uri_char) {
	if (DEBUG)
		cout << "%H at char [" << uri_char << "], buffer: " << buffer << endl; // DEBUG 

	if (buffer.back() == '%' && IsHexDig(uri_char))
		return u_Percent;
	else if (IsHexDig(buffer.back()) && IsHexDig(uri_char))
		return u_Percent_Done;
	return u_Invalid;
}

// Called after validating percent-encoded tokens and in PercentDone state.
static void	DecodePercent(string& buffer) {
	size_t	percent_start = buffer.size() - 3;
	string	newbuffer = buffer.substr(0, percent_start);
	string	hex = buffer.substr(percent_start + 1, percent_start + 2);
	char	c = std::stoi(hex, nullptr, 16);
	newbuffer += c;
	buffer = newbuffer;
} 

// Handles transition after a valid %HH sequence.
// PChar & '/' input trigger transition to either Query or Path state
// depending on if we're at the Path or Query part of the URI.
// "return URIState(_path)" leverages equivalency between pt_Path & pt_Query values
// in URIPart enum and u_Path & Query state values in the URIState enum.
// So if we're at Path part, we return the Path state. Ditto for query.
URIState		RequestTargetParser::PercentDoneHandler(char uri_char) {
	NormalizeString(toupper, buffer, buffer.size() - 2);
	DecodePercent(buffer);
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

#undef DEBUG // REMOVE