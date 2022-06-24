#include "request_utils.hpp"

bool	IsHexDig(char c) {
	return (isdigit(c) || (c >= 'A' && c <= 'F'));
}

// bool	IsPercentEncoded(char c) {

// }

// Used by IsPChar.
bool	IsUnreserved(char c) {
	return (c == '-' || c == '.' || c == '_' || c == '~'
			|| isalpha(c) || isdigit(c));
}

// Used by IsPChar.
bool	IsSubDelim(char c) {
	return (c == '!' || c == '$' || c == '&' || c == '\''
			|| c == '(' || c == ')' || c == '*' || c == '+' || c == ','
			|| c == ';' || c == '=');
}

// Used for URI::ParseString.
// Absolute-paths are at least 1 "/" followed by pchars.
// Note: doesn't check for percent-encoding. % needs to be checked
// for separately and IsHexDig called on subsequent 2 chars to validate.
bool	IsPChar(char c) {
	return (c == ':' || c == '@' || IsUnreserved(c) || IsSubDelim(c));
}

// Used by RequestParser::ParseMethod.
// Tokens are at least 1 tchar
bool	IsTChar(char c) {
	return (c == '!' || c == '#' || c == '$' || c == '%' || c == '&'
			|| c == '\'' || c == '*' || c == '+' || c == '-' || c == '.'
			|| c == '^' || c == '_' || c == '`' || c == '|' || c == '~'
			|| isalpha(c) || isdigit(c));
}

bool	IsSpace(char c) {
	return c == ' ';
}

bool	IsValidString(bool (*validity_checker)(char), string const& s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (validity_checker(s[i]) == false)
			return false;
	}
	return true;
}