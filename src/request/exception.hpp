#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <cctype> // isprint
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "request_utils.hpp"

using namespace std;

// Used for: invalid or badly formed request headers.
// Should return 400 code.
class BadRequestException : public exception {
	public:
		BadRequestException() {}

		BadRequestException(string detail) {
			string encoded_detail = EncodePercent(detail);
			_error_str = "400: Bad request";
			if (!encoded_detail.empty()) {
				_error_str += " | " + encoded_detail;
			}
		}

		virtual const char* what() const throw() {
			return _error_str.c_str();
		}

	private:
		string	_error_str;
};

// Used for: payload size exceeding 1,048,576 bytes (1mb).
// Should return 414 code.
// Server may close connection to prevent client from continuing request.
class PayloadTooLargeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("413: Payload Too Large");
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

// Used for: Content-Encoding header field in request.
// Should return 415 code.
class UnsupportedMediaTypeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("415: Unsupported Media Type");
		}
};

// Used for: Expect header field with any value except "100-continue".
// Should return 417 code.
class ExpectationFailedTypeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("417: Expectation Failed");
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

// Used for: non-recognized request method or transfer coding.
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
