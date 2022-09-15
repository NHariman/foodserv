#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <map>
#include <string>
#include "request_parser.hpp"
#include "ahttp_message.hpp"
#include "../config/nginx_config.hpp"
#include "../resolved_target/target_config.hpp"

using namespace std;

class NginxConfig;

// Inherits the following protected attributes from AHTTPMessage:
// 		std::string							_http_version;
// 		int									_status_code;
// 		std::string							_message_body;
// 		std::map<std::string, std::string>	_header_fields;
// Along with their respective getters & setters.

class Request : public AHTTPMessage {
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

		// Getters
		TargetConfig const&	GetTargetConfig() const;
		string				GetMethod() const;
		string				GetTargetString() const;
		URI const&			GetTargetURI() const;
		Status				GetStatus() const;

		// Setters
		void				SetMethod(string const& method);
		void				SetTarget(string const& target);
		void				SetStatus(Status status);
		void				SetTargetHost(string const& host);
		void				SetResolvedTargetPath(string const& target_path);
	
		// friend class forward declaration allows RequestParser to
		// access private variables of Request.
		friend class	RequestParser; // accesses _target_config
	
	private:
		TargetConfig		_target_config;
		RequestParser		_parser;
		string				_method;
		URI					_target;
		string				_buf;
		Status				_request_status;

		bool	CanParse();
		void	CheckStatus();
};

#endif /* REQUEST_HPP */
