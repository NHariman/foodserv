#include "request_utils.hpp"

// Used for validating hexademical digits following '%' inputs indicating
// percent-encoding. According to RFC 3986 2.1, lowercase digits are treated
// the same as uppercase digits. This function therefore does conversion to
// uppercase and normalizes lowercase characters.
bool	IsHexDig(char& c) {
	if (c >= 'a' && c <= 'f')
		c = toupper(c);
	return (isdigit(c) || (c >= 'A' && c <= 'F'));
}

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

// Checks if string `s` is valid according to rules of `validity_checker`
// function that's passed as argument.
bool	IsValidString(bool (*validity_checker)(char), string const& s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (validity_checker(s[i]) == false)
			return false;
	}
	return true;
}