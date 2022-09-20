#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include "request.hpp"
#include "response.hpp"

class NginxConfig;

class ResponseHandler {
	public:
		// Config file constructor
		explicit ResponseHandler(NginxConfig* config);
		// Destructor
		~ResponseHandler();

		void HandleError(Request& request);
		void HandleExpect(Request& request);
		void HandleRegular(Request& request);

	private:
		NginxConfig*	_config;
		Request*		_request;
		Response		_response;
		FileHandler		_file_handler;

		// Error page handling
		std::string FindCustomErrorPage(int error_code);
		void		HandleCustomError(std::string const& error_page_path);

		// Redirection
		bool		IsRedirected();

		void		SetStatusLine();
		// Response header setting
		void		SetDate();
		void		SetServer();
		// void		SetLastModified();
		void		SetLocation(std::string const& path);
		void		SetContentType();
		void		SetContentLength();
		void		SetConnection();
		void		SetAllow();
		std::string	GetAllowedMethodsString();
};

#endif /* RESPONSE_HANDLER_HPP */
