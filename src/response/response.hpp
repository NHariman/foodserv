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
		std::string const&	GetReasonPhrase() const;

		// Setters
		void	SetReasonPhrase(std::string const& phrase);

	private:
		std::string	_reason_phrase;
		bool		_complete;
		
};

#endif /* RESPONSE_HPP */