#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include "request.hpp"
#include "response.hpp"
#include "file_handler.hpp"

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

		void		AssignResponseResolvedPath(std::string const& path = std::string());

		// Error page handling
		std::string FindCustomErrorPage(int error_code);
		void		HandleCustomError(std::string const& error_page_path);
		void		HandleDefaultError();

		// Redirection
		bool		IsRedirected();
		void		HandleRedirection();

		// File handling
		void		ExecuteGet(bool set_code = true);

		// Response forming
		void		BuildResponse();
		void		SetStatusLine();
		void		SetHeaders();

		// Response header setting helpers
		void		SetDate();
		void		SetServer();
		void		SetLocation();
		void		SetContentType();
		void		SetContentLength();
		void		SetConnection();
		void		SetAllow();
		std::string	GetAllowedMethodsString();
};

#endif /* RESPONSE_HANDLER_HPP */
