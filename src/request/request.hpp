#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include "request_parser.hpp"
#include "request_line_parser.hpp"
#include "../config/nginx_config.hpp"

using namespace std;

// returned by GetField when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

class Request {
	public:
		// Default constructor
		Request();
		// C-string constructor
		explicit Request(NginxConfig* config, char const* buffer);
		// Destructor
		~Request();

		size_t	bytes_read; // bytes read of request input
		ssize_t	content_length; // bytes of payload body, signed so can be initialized to -1
		size_t	max_body_size;

		string		GetMethod() const;
		string		GetTarget() const;
		URI const&	GetURI() const;
		string		GetVersion() const;
		string		GetField(string field_name) const;
		string		GetMessageBody() const;
	
		// friend class forward declaration allows RequestParser to
		// access private & protected members of Request.
		friend class RequestParser;
		friend class ChunkedParser;
	
	private:
		struct RequestLine	request_line;
		map<string, string>	header_fields;
		string				msg_body;
};

#endif /* REQUEST_HPP */
