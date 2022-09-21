#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <map>
#include "ahttp_message.hpp"

// Inherits the following attributes from AHTTPMessage:
// 		std::string							_http_version;
// 		int									_status_code;
// 		std::string							_message_body;
// 		std::map<std::string, std::string>	_header_fields;
// 		size_t								_content_length;
// Along with their respective getters & setters.

class Response : public AHTTPMessage {
	public:
		// Default constructor
		Response();
		// Destructor
		~Response();

		bool	IsComplete() const;

		// Getters
		std::istream*		GetFileStream() const;
		std::string const&	GetReasonPhrase() const;
		std::string const&	GetResolvedPath() const;

		// Setters
		void	SetFileStream(std::istream* stream);
		void	SetReasonPhrase(std::string const& phrase);
		void	SetResolvedPath(std::string const& path);

	private:
		std::istream*	_stream;
		std::string		_reason_phrase;
		std::string		_resolved_path;
		bool			_complete;
		
};

#endif /* RESPONSE_HPP */
