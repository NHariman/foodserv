#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <cctype> // isprint
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "../utils/request_utils.hpp"

// Exception interface for returning error codes.
namespace http {
class	exception : public std::exception {
	public:
		// exception() {}
		// virtual ~exception()  throw() { return; }
		virtual int	which() const  throw() = 0;
};
} // namespace http

// Used for: invalid or badly formed request headers.
// Thrown by:	HeaderFieldParser, RequestValidator, RequestLineParser,
//				RequestParser, RequestTargetParser, URIHostParser, URI classes.
// Should return 400 code.
class BadRequestException : public http::exception {
	public:
		BadRequestException() {}
		virtual ~BadRequestException() throw() { return; }

		BadRequestException(std::string detail) {
			std::string encoded_detail = EncodePercent(detail);
			_error_str = "400: Bad request";
			if (!encoded_detail.empty()) {
				_error_str += " | " + encoded_detail;
			}
		}

		virtual const char* what() const throw() {
			return _error_str.c_str();
		}

		int	which() const throw() {
			return 400;
		}

	private:
		std::string	_error_str;
};

// Used for: resource is unable to be accessed.
// Thrown by FileHandler::GetFileContents.
// Should return 403 code.
class LengthRequiredException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("403: Forbidden");
		}

		int	which() const throw() {
			return 403;
		}
};

// Used for: request containing message body but no Content-Length header.
// Thrown by RequestParser::AfterParseCheck.
// Should return 411 code.
class LengthRequiredException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("411: Length Required");
		}

		int	which() const throw() {
			return 411;
		}
};

// Used for: payload size exceeding max (default 1,048,576 bytes (1mb)).
// Thrown by RequestValidator::ValidContentLength &
//			ChunkedParser::SizeHandler, ::DataHandler, ::LastHandler.
// Should return 413 code.
// Server may close connection to prevent client from continuing request.
class PayloadTooLargeException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("413: Payload Too Large");
		}

		int	which() const throw() {
			return 413;
		}
};

// Used for: URI exceeding 8192 bytes (8kb).
// Thrown by RequestTargetParser::PreParseCheck.
// Should return 414 code.
class URITooLongException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("414: URI Too Long");
		}

		int	which() const throw() {
			return 414;
		}
};

// Used for: Content-Encoding header field in request.
// Thrown by RequestValidator::ValidContentEncoding.
// Should return 415 code.
class UnsupportedMediaTypeException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("415: Unsupported Media Type");
		}

		int	which() const throw() {
			return 415;
		}
};

// Used for: Expect header field with any value except "100-continue".
// Thrown by RequestValidator::ValidExpect.
// Should return 417 code.
class ExpectationFailedTypeException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("417: Expectation Failed");
		}

		int	which() const throw() {
			return 417;
		}
};

// Used for: request header fields in total or a single one exceeds
// 8192 bytes (8kb) (following IBM & Apache).
// Thrown by HeaderFieldParser::GetNextState, ::NameHandler, ::ValueHandler.
// Should return 431 code.
class RequestHeaderFieldsTooLargeException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("431: Request Header Fields Too Large");
		}

		int	which() const throw() {
			return 431;
		}
};

// Used for: non-recognized request method or transfer coding.
// Thrown by:	RequestLineParser::MethodHandler,
// 				RequestValidator::ValidTransferEncoding.
// Should return 501 code.
class NotImplementedException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("501: Not Implemented");
		}

		int	which() const throw() {
			return 501;
		}
};

// Used for: when request states something other than HTTP/1.1.
// Thrown by RequestLineParser::VersionHandler.
// Should return 505 code.
class HTTPVersionNotSupportedException : public http::exception {
	public:
		virtual const char* what() const throw() {
			return ("505: HTTP Version Not Supported");
		}

		int	which() const throw() {
			return 505;
		}
};

#endif /* EXCEPTION_HPP */
