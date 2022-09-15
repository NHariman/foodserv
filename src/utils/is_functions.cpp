#include <cctype> // isalpha, isdigit, toupper
#include <iostream>

using namespace std;

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
