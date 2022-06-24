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

// Used for: URI exceeding 8190 bytes.
// Should return 414 code.
class URITooLongException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("414: URI Too Long");
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

#endif /* EXCEPTION_HPP */
