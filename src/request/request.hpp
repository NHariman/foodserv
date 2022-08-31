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

class Request {
	public:
		enum class Status {
			Bad = -1,
			Complete = 0,
			Incomplete,
			Expect
		};

		typedef std::map<string, string>	FieldsMap;

		// Default constructor
		Request();
		// Config file constructor
		explicit Request(NginxConfig* config);
		// Destructor
		~Request();

		size_t	bytes_read; // bytes read of request input
		size_t	msg_bytes_read; // bytes read of payload body
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
		Status				GetStatus() const;
		int					GetStatusCode() const;
		void				SetStatus(Status status);
	
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
		Status				_status;
		int					_status_code;

		bool	CanParse();
		void	CheckStatus();
};

#endif /* REQUEST_HPP */
