#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <iostream>
#include <string>
#include <map>

#include "exception.hpp"
#include "request_utils.hpp"
#include "uri.hpp"

using namespace std;

struct RequestLine {
	string	method;
	URI		target;
	string	version;
};

class RequestParser {
	public:
		RequestParser();
		~RequestParser();

		void	ParseRequest(char const* buffer);

	private:
		struct RequestLine _request_line;
		size_t	_bytes_read;

		size_t	ParseRequestLine(string const& message);
		size_t	ParseMethod(string const& message);
		size_t	ParseTarget(string const& message, size_t start);
};

#endif /* REQUESTPARSER_HPP */
