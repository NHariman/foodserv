#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream> // ifstream
#include <memory> // shared_ptr
#include <map>
#include "../request/http_message.hpp"

// Inherits the following attributes from HTTPMessage:
// 		std::string							_http_version;
// 		int									_status_code;
// 		std::string							_message_body;
// 		std::map<std::string, std::string>	_header_fields;
// 		size_t								_content_length;
// Along with their respective getters & setters.

class Response : public HTTPMessage {
	public:
		typedef std::shared_ptr<Response>	pointer;

		// Default constructor
		Response();
		// Assignment operator
		Response&	operator=(Response const& other);
		// Destructor
		~Response();

		bool	IsComplete() const;

		// Getters
		std::istream*		GetBodyStream() const;
		std::string const&	GetReasonPhrase() const;
		std::string const&	GetRequestTarget() const;
		std::string const&	GetResolvedPath() const;
		std::string			GetFieldsAsString() const;
		std::string&		GetCompleteResponseString();

		// Setters
		void	SetBodyStream(std::istream* stream);
		void	SetReasonPhrase(std::string const& phrase);
		void	SetRequestTarget(std::string const& path);
		void	SetResolvedPath(std::string const& path);
		void	SetComplete(bool value = true);

	private:
		std::istream*	_body_stream;
		std::string		_send_buffer;
		std::string		_reason_phrase;
		std::string		_request_target;
		std::string		_resolved_path;
		bool			_complete;
		
};

#endif /* RESPONSE_HPP */
