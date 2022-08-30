#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include "request_parser.hpp"
#include "../config/nginx_config.hpp"

using namespace std;

// returned by GetField when no field by the passed name is found.
#define NO_VAL "NO SUCH HEADER FIELD"

struct RequestLine;
class NginxConfig;
class URI;

// enum	RequestStatus {
// 	BAD = -1,
// 	DONE = 0,
// 	EXPECT,

// }

class Request {
	public:
		typedef std::map<string, string>	FieldsMap;

		// Default constructor
		Request();
		// Config file constructor
		explicit Request(NginxConfig* config);
		// Destructor
		~Request();

		size_t	bytes_read; // bytes read of request input
		ssize_t	content_length; // bytes of payload body, signed so can be initialized to -1
		size_t	max_body_size;

		size_t				Parse(char const* buffer);
		string				GetMethod() const;
		string				GetTarget() const;
		URI const&			GetURI() const;
		string				GetVersion() const;
		string				GetField(string field_name) const;
		FieldsMap const&	GetFields() const;
		string				GetMessageBody() const;
		bool				IsComplete() const;
	
		// friend class forward declaration allows RequestParser to
		// access private `_request_line`, `_header_fields`, `_msg_body`
		// attributes of Request.
		friend class	RequestParser;
		friend class	ChunkedParser;
	
	private:
		RequestParser		_parser;
		struct RequestLine	_request_line;
		FieldsMap			_header_fields;
		string				_msg_body;
		string				_buf;
		bool				_is_complete;

		bool	CanParse();
};

#endif /* REQUEST_HPP */
