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
// Thrown by:	HeaderFieldParser, HeaderFieldValidator, RequestLineParser,
//				RequestParser, RequestTargetParser, URIHostParser, URI classes.
// Should return 400 code.
class BadRequestException : public exception {
	public:
		BadRequestException() {}
		virtual ~BadRequestException() throw() { return; }

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

// Used for: request containing message body but no Content-Length header.
// Thrown by RequestParser::AfterParseCheck.
// Should return 411 code.
class LengthRequiredException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("411: Length Required");
		}
};

// Used for: payload size exceeding 1,048,576 bytes (1mb).
// Thrown by HeaderFieldValidator::ValidContentLength.
// Should return 413 code.
// Server may close connection to prevent client from continuing request.
class PayloadTooLargeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("413: Payload Too Large");
		}
};

// Used for: URI exceeding 8192 bytes (8kb).
// Thrown by RequestTargetParser::PreParseCheck.
// Should return 414 code.
class URITooLongException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("414: URI Too Long");
		}
};

// Used for: Content-Encoding header field in request.
// Thrown by HeaderFieldValidator::ValidContentEncoding.
// Should return 415 code.
class UnsupportedMediaTypeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("415: Unsupported Media Type");
		}
};

// Used for: Expect header field with any value except "100-continue".
// Thrown by HeaderFieldValidator::ValidExpect.
// Should return 417 code.
class ExpectationFailedTypeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("417: Expectation Failed");
		}
};

// Used for: request header fields in total or a single one exceeds
// 8192 bytes (8kb) (following IBM & Apache).
// Thrown by HeaderFieldParser::PreParseCheck.
// Should return 431 code.
class RequestHeaderFieldsTooLargeException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("431: Request Header Fields Too Large");
		}
};

// Used for: non-recognized request method or transfer coding.
// Thrown by:	RequestLineParser::MethodHandler,
// 				HeaderFieldValidator::ValidTransferEncoding.
// Should return 501 code.
class NotImplementedException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("501: Not Implemented");
		}
};

// Used for: when request states something other than HTTP/1.1.
// Thrown by RequestLineParser::VersionHandler.
// Should return 505 code.
class HTTPVersionNotSupportedException : public exception {
	public:
		virtual const char* what() const throw() {
			return ("505: HTTP Version Not Supported");
		}
};

#endif /* EXCEPTION_HPP */
