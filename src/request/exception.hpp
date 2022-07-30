#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <cctype> // isprint
#include <exception>
#include <iomanip> // setw
#include <iostream>
#include <sstream> // ostringstream
#include <string>

using namespace std;

// Converts non-printable characters in string to percent-encoded values
// for safe printing of error messages.
static string EncodePercent(string const& s) {
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

// Used for: invalid or badly formed request headers.
// Should return 400 code.
class BadRequestException : public exception {
	public:
		BadRequestException() {}

		BadRequestException(string const& detail)
			: _detail(EncodePercent(detail)) {}

		virtual const char* what() const throw() {
			if (!_detail.empty())
				return (("400: Bad request | " + _detail).c_str());
			return ("400: Bad request");
		}

	private:
		string	_detail;
};

// Used for: URI exceeding 8192 bytes (8kb).
// Should return 414 code.
class URITooLongException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("414: URI Too Long");
		}
};

// Used for: request header fields in total or a single one exceeds
// 8192 bytes (8kb) (following IBM & Apache).
// Should return 431 code.
class RequestHeaderFieldsTooLargeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("431: Request Header Fields Too Large");
		}
};

// Used for: method not implemented.
// Should return 501 code.
class NotImplementedException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("501: Method Not Implemented");
		}
};

// Used for: when request states something other than HTTP/1.1.
// Should return 505 code.
class HTTPVersionNotSupportedException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("505: HTTP Version Not Supported");
		}
};

#endif /* EXCEPTION_HPP */
