#include "uri_host_parser.hpp"
#define DEBUG 0 // TODO: remove
// Default constructor
URIHostParser::URIHostParser()
	:	StateParser(h_Start), _uri_host(NULL), _groups(0), _literal(false) {}

// Destructor
URIHostParser::~URIHostParser() {}

// Resets internal counters (in case of repeat calls) and passes
// input string to StateParser::ParseString().
size_t	URIHostParser::Parse(string& uri_host, string const& input) {
	_groups = 0;
	_literal = false;
	_uri_host = &uri_host;
	return ParseString(input);
}

HostState	URIHostParser::GetNextState(size_t pos) {
	static 	HostState (URIHostParser::*table[])(size_t pos) = {
			&URIHostParser::StartHandler,
			&URIHostParser::LiteralHandler,
			&URIHostParser::IPv6Handler,
			&URIHostParser::IPvFHandler,
			&URIHostParser::IPv4Handler,
			&URIHostParser::LiteralEndHandler,
			&URIHostParser::RegNameHandler,
			&URIHostParser::RegNamePctHandler,
			&URIHostParser::RegNamePctDoneHandler,
			&URIHostParser::PortHandler,
			nullptr
	};
	if (DEBUG) cout << "GetNextState: at [" << input[pos] << "] & state: "
		<< cur_state << " & groups: " << _groups << endl;
	return (this->*table[cur_state])(pos);
}

void	URIHostParser::CheckInvalidState() const {
	if (cur_state == h_Invalid)
		throw BadRequestException("Invalid token in host URI: \"" + buffer + "\"");
}

bool	URIHostParser::CheckDoneState() {
	return (cur_state == h_Done);
}

// Checks if there's illegal characters after terminating char.
void	URIHostParser::AfterParseCheck(size_t& pos) { 
	if (cur_state == h_Done && pos < input.size() - 1)
		throw BadRequestException("Extra characters after terminating token in URI host");
	else
		*_uri_host = buffer;
}

static HostState	SkipEOL(bool& skip_char) {
	skip_char = true;
	return h_Done;
}

static bool	IsUnreservedSubDelim(char c) {
	return (IsUnreserved(c) || IsSubDelim(c));
}

// if string is only digits, with 3 periods, assume it's IPv4
static bool	IsIPv4Format(string const& s) {
	if (DEBUG) cout << "IsIPv4Format: IsValidString = " << IsValidString(isdigit, s, ".")
		<< " & period count = " << std::count(s.begin(), s.end(), '.') << endl;
	return (IsValidString(isdigit, s, ".")
			&& std::count(s.begin(), s.end(), '.') == 3);
}

// Handles transition into IP-literal, reg-name, or IPv4 parsing,
// depending on token.
HostState	URIHostParser::StartHandler(size_t pos) {
	if (DEBUG) cout << "StartHandler: at [" << input[pos] << "]\n";
	switch (input[pos]) {
		case '\0':
			return SkipEOL(skip_char);
		case '[': {
			_literal = true;
			return h_Literal;
		}
		case '%':
			return h_RegNamePct;
		default:
			// check if input fits IPv4 formatting
			if (IsIPv4Format(input))
				return h_IPv4;
			// otherwise we assume it's reg-name format
			else if (IsUnreservedSubDelim(input[pos]))
				return h_RegName;
			else
				return h_Invalid;
	}
}

// Handles IP-literals, signalled by starting '[' token.
HostState	URIHostParser::LiteralHandler(size_t pos) {
	if (DEBUG) cout << "LiteralHandler: at [" << input[pos] << "]\n";
	switch (input[pos]) {
		case 'v':
			return h_IPvF;
		case ':':
			return h_IPv6;
		default:
			if (IsHexDig(input[pos]))
				return h_IPv6;
			else
				return h_Invalid;
	}
}

static bool	ValidLastBitsIPv4(string const& input, size_t pos) {
	if (input[pos - 1] == ':' && isdigit(input[pos])) {
		size_t	end = input.find_first_of(']', pos);
		string	last_bits = input.substr(pos, end - pos);

		return (IsIPv4Format(last_bits));
	}
	return false;
}

// Handles IPv6 address parsing.
// IPv6 addresses are composed of 8 groups of 1-4 hexadecimal digits,
// separated by ':'. Double colons denote a sequential group of 0s 
// that have been elided (e.g. 0:0:0:0:0:0:0:1 may be reduced to just ::1).
HostState	URIHostParser::IPv6Handler(size_t pos) {
	if (DEBUG) cout << "IPv6Handler: at [" << input[pos] << "]\n";
	static size_t	colon_count = 0;
	switch (input[pos]) {
		case ']':
			if (_groups >= 1)
				return h_LiteralEnd;
		case ':': {
			if (colon_count > 1) // only max 2 sequential colons allowed
				return h_Invalid;
			colon_count += 1;
			_groups += 1;
			return h_IPv6;
		}
		default:
			// when 2 least-significant last bits are in IPv4 format
			if (ValidLastBitsIPv4(input, pos)) {
				_groups = 0;
				return h_IPv4;
			}
			else if (IsHexDig(input[pos])) {
				colon_count = 0;
				return h_IPv6;
			}
			else
				return h_Invalid;
	}
}

// Handles IPvFuture address parsing, signalled by starting 'v' token.
// IPvFuture requires sequence of:
// 		"v" - at least 1 HEXDIG - "." - at least 1 Unreserved/SubDelim/":"
HostState	URIHostParser::IPvFHandler(size_t pos) {
	if (DEBUG) cout << "IPvFHandler: at [" << input[pos] << "]\n";
	_groups += 1;
	switch (input[pos]) {
		case ']':
			if (_groups >= 4)
				return h_LiteralEnd;
		case '.':
			if (IsHexDig(buffer.back()))
				return h_IPvF;
		default:
			if (PrecededBy(buffer, 'v') && IsHexDig(input[pos]))
				return h_IPvF;
			else if (IsUnreservedSubDelim(input[pos]) || input[pos] == ':')
				return h_IPvF;
			else
				return h_Invalid;			
	}
}

// Used by IPv4Handler to validate dec-octet group.
static bool	ValidDecOctetGroup(string const& buffer) {
	size_t	begin = buffer.find_last_of('.');
	int		octet;

	// if 1st group
	if (begin == string::npos) {
		if (buffer.find(":") != string::npos) { // if part of IPv6 address
			size_t	start_of_ipv4 = buffer.find_last_of(":") + 1;
			octet = std::stoi(buffer.substr(start_of_ipv4));
		}
		else
			octet = std::stoi(buffer);
	}
	// if latter group
	else
		octet = std::stoi(buffer.substr(begin + 1));
	if (octet < 0 || octet > 255)
		return false;
	return true;
}

// Handles IPv4 address parsing.
// IPv4 addresses are composed of 4 groups of 1-3 digits, delimited by '.'.
HostState	URIHostParser::IPv4Handler(size_t pos) {
	if (DEBUG) cout << "IPv4Handler: at [" << input[pos] << "]\n";
	static size_t digit_counter = 0;

	switch (input[pos]) {
		case '\0':
			if (_groups == 4)
				return SkipEOL(skip_char);
		case ':':
			if (_groups == 4)
				return h_Port;
		case ']':
			if (_literal && _groups == 12) // if ending IP-literal
				return h_LiteralEnd;
		case '.':
			if (isdigit(buffer.back()) && ValidDecOctetGroup(buffer))
				return h_IPv4;
		default:
			if (isdigit(input[pos])) {
				// if more than 3 digit group
				if (digit_counter > 3)
					return h_Invalid;
				// if start of new group of digits
				if (PrecededBy(buffer, '.') || _groups == 0) {
					digit_counter = 1;
					_groups += 1;
				}
				else
					digit_counter += 1;
				return h_IPv4;
			}
			else
				return h_Invalid;
	}
}

// Handles transition from IP-literal once ending ']' token is found.
HostState	URIHostParser::LiteralEndHandler(size_t pos) {
	if (DEBUG) cout << "LiteralEndHandler: at [" << input[pos] << "]\n";
	switch (input[pos]) {
		case '\0':
			return SkipEOL(skip_char);
		case ':':
			return h_Port;
		default:
			return h_Invalid;
	}
}

// Handles reg-name parsing.
HostState	URIHostParser::RegNameHandler(size_t pos) {
	if (DEBUG) cout << "RegNameHandler: at [" << input[pos] << "]\n";
	switch (input[pos]) {
		case '\0':
			return SkipEOL(skip_char);
		case ':':
			return h_Port;
		case '%':
			return h_RegNamePct;
		default:
			if (IsUnreservedSubDelim(input[pos]))
				return h_RegName;
			else
				return h_Invalid;
	}
}

// Handles transition after percent-encoding has been found (% input).
// Checks if subsequent 2 characters are valid hexadecimal digits.
HostState	URIHostParser::RegNamePctHandler(size_t pos) {
	if (DEBUG) cout << "RegNamePctHandler: at [" << input[pos] << "]\n";
	if (PrecededBy(buffer, '%') && IsHexDig(input[pos]))
		return h_RegNamePct;
	else if (IsHexDig(buffer.back()) && IsHexDig(input[pos]))
		return h_RegNamePctDone;
	return h_Invalid;
}

// Handles transition after a valid %HH sequence.
HostState	URIHostParser::RegNamePctDoneHandler(size_t pos) {
	NormalizeString(toupper, buffer, buffer.size() - 2);
	buffer = DecodePercent(buffer);
	switch (input[pos]) {
		case '\0':
			return SkipEOL(skip_char);
		case '%':
			return h_RegNamePct;
		default:
			if (IsUnreservedSubDelim(input[pos]))
				return h_RegName;
			else
				return h_Invalid;
	}
}

// Checks for digits in port after ':' has been previously found.
HostState	URIHostParser::PortHandler(size_t pos) {
	if (DEBUG) cout << "PortHandler: at [" << input[pos] << "]\n";
	if (input[pos] == '\0')
		return SkipEOL(skip_char);
	else if (isdigit(input[pos]))
		return h_Port;
	else
		return h_Invalid; 
}
#undef DEBUG // TODO: remove