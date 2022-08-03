#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include "request_parser.hpp"
#include "request_line_parser.hpp"

using namespace std;

// returned by GetField when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

class Request {
	public:
		// Default constructor
		Request();
		// C-string constructor
		explicit Request(char const* buffer);

		// Destructor
		~Request();

		string	msg_body;
		size_t	bytes_read;
		struct RequestLine	request_line;
		map<string, string>	header_fields;

		string		GetMethod() const;
		string		GetTarget() const;
		URI const&	GetURI() const;
		string		GetVersion() const;
		string		GetField(string field_name) const;
		string		GetMessageBody() const;
};

#endif /* REQUEST_HPP */
