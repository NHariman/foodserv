#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream> // ifstream
#include <map>
#include "../request/ahttp_message.hpp"

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
		// Assignment operator
		// Response&	operator=(Response const& other);
		// Destructor
		~Response();

		bool	IsComplete() const;

		// Getters
		std::istream*		GetFileStream() const;
		std::string const&	GetReasonPhrase() const;
		std::string const&	GetResolvedPath() const;
		std::istream*		GetCompleteResponse() const;

		// Setters
		void	SetFileStream(std::istream* stream);
		void	SetReasonPhrase(std::string const& phrase);
		void	SetResolvedPath(std::string const& path);
		void	SetComplete();

	private:
		std::istream*	_stream;
		std::string		_reason_phrase;
		std::string		_resolved_path;
		bool			_complete;
		
};

#endif /* RESPONSE_HPP */
