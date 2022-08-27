#include "request_utils.hpp"

// Used for validating hexademical digits following '%' inputs indicating
// percent-encoding.
bool	IsHexDig(int c) {
	return (isdigit(c)
			|| (c >= 'A' && c <= 'F')
			|| (c >= 'a' && c <= 'f'));
}

// Used by IsPChar.
bool	IsUnreserved(int c) {
	return (c == '-' || c == '.' || c == '_' || c == '~'
			|| isalpha(c) || isdigit(c));
}

// Used by IsPChar.
bool	IsSubDelim(int c) {
	return (c == '!' || c == '$' || c == '&' || c == '\''
			|| c == '(' || c == ')' || c == '*' || c == '+' || c == ','
			|| c == ';' || c == '=');
}

// Used for URI::ParseString.
// Absolute-paths are at least 1 "/" followed by pchars.
// Note: doesn't check for percent-encoding. % needs to be checked
// for separately and IsHexDig called on subsequent 2 chars to validate.
bool	IsPChar(int c) {
	return (c == ':' || c == '@' || IsUnreserved(c) || IsSubDelim(c));
}

// Used by RequestParser::ParseMethod.
// Tokens are at least 1 tchar
bool	IsTChar(int c) {
	return (c == '!' || c == '#' || c == '$' || c == '%' || c == '&'
			|| c == '\'' || c == '*' || c == '+' || c == '-' || c == '.'
			|| c == '^' || c == '_' || c == '`' || c == '|' || c == '~'
			|| isalpha(c) || isdigit(c));
}

// Used for header field value parsing.
bool	IsVChar(int c) {
	return (c >= '!' && c <= '~');
}

bool	IsSpace(int c) {
	return c == ' ';
}

bool	IsOctet(int c) {
	return (c >= 0x00 && c <= 0xFF);
}

// Checks if character is whitespace as defined by RFC 7230 (space or horizontal tab).
bool	IsWhitespace(int c) {
	return (c == ' ' || c == '\t');
}

// Checks if string `s` is valid according to rules of `validity_checker`
// function that's passed as argument.
// Optional argument `allow` allows for certain characters in string.
bool	IsValidString(int (*validity_checker)(int), string const& s,
							string const& allow) {
	for (size_t i = 0; i < s.size(); i++) {
		if (validity_checker(s[i]) == false && allow.find(s[i]) == string::npos)
			return false;
	}
	return true;
}

// Used by RequestTargetParser & URIHostParser to check if previously-read char
// (that's been pushed to buffer) is `c`.
bool	PrecededBy(string const& read_buf, char c) {
	return (read_buf.back() == c);
}

// Used by RequestParser and RequestTargetParser to normalize input
// to either lower or uppercase.
void	NormalizeString(int (*convert)(int), string& s, size_t start) {
	std::transform(s.begin() + start, s.end(), s.begin() + start, convert);
}

// Used by BadRequestException to safely print error messages.
// Converts non-printable characters in string to percent-encoded values.
string EncodePercent(string const& s) {
    stringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = s.begin(); i != s.end(); ++i) {
        string::value_type c = (*i);
        // Keep printable characters
        if (isprint(c)) {
            escaped << c;
            continue;
        }
        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << static_cast<unsigned>(c);
        escaped << nouppercase;
    }
    return escaped.str();
}

// Used by RequestTargetParser and URIHostParser to decode percent-encoded values.
string	DecodePercent(string const& s) {
	size_t	percent_start = s.size() - 3;
	string	new_s = s.substr(0, percent_start);
	string	hex = s.substr(percent_start + 1, percent_start + 2);

	// Check for encoded CR and LF that might be used in response splitting.
	if (hex == "0D" || hex == "0A")
		throw BadRequestException("Bad octets found in encoded data");
	
	char	c = std::stoi(hex, nullptr, 16);
	new_s += c;
	return new_s;
} 

size_t	MBToBytes(size_t size_mb) {
	return size_mb * 1048576;
}

size_t	HextoDec(string hex_string) {
	size_t n;

	std::istringstream(hex_string) >> std::hex >> n;
	return n;
}
