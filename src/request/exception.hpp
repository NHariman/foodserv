#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>

using namespace std;

// Used for: invalid or badly formed request headers.
// Should return 400 code.
class BadRequestException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("400: Bad request");
		}
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
			return ("501: Not Implemented");
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