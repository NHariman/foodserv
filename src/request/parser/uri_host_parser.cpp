#include "uri_host_parser.hpp"
#include "../uri.hpp"

// Default constructor
URIHostParser::URIHostParser()
	:	AStateParser(h_Start, h_Done),
		_uri(NULL),
		_groups(0),
		_colons(0),
		_digits(0),
		_literal(false) {}

// Destructor
URIHostParser::~URIHostParser() {}

// Resets internal counters (in case of repeat calls) and passes
// input string to AStateParser::ParseString().
size_t	URIHostParser::Parse(URI& uri, std::string const& input) {
	_groups = 0;
	_colons = 0;
	_digits = 0;
	_literal = false;
	_uri= &uri;
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
	skip_char = false;
	return (this->*table[cur_state])(pos);
}

void	URIHostParser::CheckInvalidState() const {
	if (cur_state == h_Invalid)
		throw BadRequestException("Invalid token in host URI: \"" + buffer + "\"");
}

// Checks if there's illegal characters after terminating char.
void	URIHostParser::AfterParseCheck() { 
	if (cur_state == h_Done && pos < input.size() - 1)
		throw BadRequestException("Extra characters after terminating token in URI host");
}

static bool	IsUnreservedSubDelim(char c) {
	return (IsUnreserved(c) || IsSubDelim(c));
}

// if string is only digits, with at least 1 periods, assume it's IPv4
static bool	IsIPv4Format(std::string const& s) {
	return (IsValidString(isdigit, s, ".:-") // allows '.' for IPv4 delim & ':' for port
			&& std::count(s.begin(), s.end(), '.') > 1);
}

// Handles transition into IP-literal, reg-name, or IPv4 parsing,
// depending on token.
HostState	URIHostParser::StartHandler(size_t pos) {
	switch (input[pos]) {
		case '\0':
			return PushBuffer(_uri->_host, h_Done);
		case '[':
			_literal = true;
			return h_Literal;
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

static bool	ValidLastBitsIPv4(std::string const& input, size_t pos) {
	if (input[pos - 1] == ':' && isdigit(input[pos])) {
		size_t	end = input.find_first_of(']', pos);
		std::string	last_bits = input.substr(pos, end - pos);

		return (IsIPv4Format(last_bits));
	}
	return false;
}

// Used by IPv6Handler when a ':' is found. Increments colon & group count,
// and resets digit count.
static HostState	HandleIPv6Colon(size_t& colons, size_t& digits, size_t& groups) {
	if (colons > 1) // only max 2 sequential colons allowed
		return h_Invalid;
	colons += 1;
	digits = 0;
	groups += 1;
	return h_IPv6;
}

// Used by IPv6Handler to handle digit input transition.
// Resets colon_count and increments digit count.
static HostState	HandleIPv6Digit(size_t& colons, size_t& digits) {
	// cannot exceed 4 hexadecimal digits in a group
	if (digits > 3)
		return h_Invalid;
	colons = 0;
	digits += 1;
	return h_IPv6;
}

// Used by IPv6Handler to transform uppercase hex-alpha to lowercase.
static void	NormalizeIPv6HexDig(std::string& buffer, char c, bool& skip_char) {
	if (c >= 'A' && c <= 'Z') {
		buffer += tolower(c);
		skip_char = true;
	}
}

// Handles IPv6 address parsing.
// IPv6 addresses are composed of 8 groups of 1-4 hexadecimal digits,
// separated by ':'. Double colons denote a sequential group of 0s 
// that have been elided (e.g. 0:0:0:0:0:0:0:1 may be reduced to just ::1).
HostState	URIHostParser::IPv6Handler(size_t pos) {

	switch (input[pos]) {
		case ']':
			if (_groups >= 1)
				return h_LiteralEnd;
			break;
		case ':':
			return HandleIPv6Colon(_colons, _digits, _groups);
		default:
			// when 2 least-significant last bits are in IPv4 format
			if (ValidLastBitsIPv4(input, pos)) {
				_groups = 0;
				_digits = 0;
				return h_IPv4;
			}
			else if (IsHexDig(input[pos])) {
				NormalizeIPv6HexDig(buffer, input[pos], skip_char);
				return HandleIPv6Digit(_colons, _digits);
			}
			else
				return h_Invalid;
	}
	return h_Invalid;
}

// Handles IPvFuture address parsing, signalled by starting 'v' token.
// IPvFuture requires sequence of:
// 		"v" - at least 1 HEXDIG - "." - at least 1 Unreserved/SubDelim/":"
HostState	URIHostParser::IPvFHandler(size_t pos) {
	_groups += 1;
	switch (input[pos]) {
		case ']':
			if (_groups >= 4)
				return h_LiteralEnd;
			break;
		case '.':
			if (IsHexDig(buffer.back()))
				return h_IPvF;
			break;
		default:
			if (PrecededBy(buffer, 'v') && IsHexDig(input[pos]))
				return h_IPvF;
			else if (IsUnreservedSubDelim(input[pos]) || input[pos] == ':')
				return h_IPvF;
			else
				return h_Invalid;			
	}
	return h_Invalid;
}

// Used by IPv4Handler to validate dec-octet group,
// which has to be within range of 0 to 255.
static bool	ValidDecOctetGroup(std::string const& buffer) {
	size_t	begin = buffer.find_last_of('.');
	int		octet;

	// if 1st group
	if (begin == std::string::npos) {
		if (buffer.find(":") != std::string::npos) { // if part of IPv6 address
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

// Used by IPv4Handler to handle digit input transition.
// Increments digit count (or resets it with new group).
static HostState	HandleIPv4Digits(size_t& digits, size_t& groups,
										std::string const& buffer) {
	// if more than 3 digit group
	if (digits > 3)
		return h_Invalid;
	// if start of new group of digits
	if (PrecededBy(buffer, '.') || groups == 0) {
		digits = 1;
		groups += 1;
	}
	else
		digits += 1;
	return h_IPv4;
}

// Handles IPv4 address parsing.
// IPv4 addresses are composed of 4 groups of 1-3 digits, delimited by '.'.
HostState	URIHostParser::IPv4Handler(size_t pos) {
	switch (input[pos]) {
		case '\0':
			if (_groups == 4 && ValidDecOctetGroup(buffer))
				return PushBuffer(_uri->_host, h_Done);
			break;
		case ':':
			if (_groups == 4)
				return PushBuffer(_uri->_host, h_Port);
			break;
		case ']':
			if (_literal && _groups == 4)
				return h_LiteralEnd;
			break;
		case '.':
			if (isdigit(buffer.back()) && ValidDecOctetGroup(buffer))
				return h_IPv4;
			break;
		default:
			if (isdigit(input[pos]))
				return HandleIPv4Digits(_digits, _groups, buffer);
			else
				return h_Invalid;
	}
	return h_Invalid;
}

// Handles transition from IP-literal once ending ']' token is found.
HostState	URIHostParser::LiteralEndHandler(size_t pos) {
	switch (input[pos]) {
		case '\0':
			return PushBuffer(_uri->_host, h_Done);
		case ':':
			return PushBuffer(_uri->_host, h_Port);
		default:
			return h_Invalid;
	}
}

// Handles reg-name parsing.
HostState	URIHostParser::RegNameHandler(size_t pos) {
	switch (input[pos]) {
		case '\0':
			return PushBuffer(_uri->_host, h_Done);
		case ':':
			return PushBuffer(_uri->_host, h_Port);
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
	if (PrecededBy(buffer, '%') && IsHexDig(input[pos]))
		return h_RegNamePct;
	else if (IsHexDig(buffer.back()) && IsHexDig(input[pos]))
		return h_RegNamePctDone;
	return h_Invalid;
}

// Handles transition after a valid %HH sequence.
HostState	URIHostParser::RegNamePctDoneHandler(size_t pos) {
	NormalizeString(toupper, buffer, buffer.size() - 2);
	buffer = DecodePercent(buffer, buffer.size() - 3);
	switch (input[pos]) {
		case '\0':
			return PushBuffer(_uri->_host, h_Done);
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
	if (input[pos] == '\0')
		return PushBuffer(_uri->_port, h_Done);
	else if (isdigit(input[pos]))
		return h_Port;
	else
		return h_Invalid; 
}

// Called when ":" signalling port or EOL is found.
// Pushes buffer to URI::host or port, clears buffer, and return `next_state`.
HostState	URIHostParser::PushBuffer(std::string& field, HostState next_state) {
	if (!buffer.empty()) {
		field = buffer;
		buffer.clear();
	}
	skip_char = true;
	return next_state;
}
