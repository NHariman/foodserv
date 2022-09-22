#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include "response.hpp"
#include "file_handler.hpp"
#include "../err/error_responses.hpp"
#include "../request/request.hpp"

class NginxConfig;

class ResponseHandler {
	public:
		// Config file constructor
		explicit ResponseHandler(NginxConfig* config);
		// Destructor
		~ResponseHandler();

		bool	Ready();
		void	Send();
		void	HandleError(Request& request);
		void	HandleExpect(Request& request);
		void	HandleRegular(Request& request);

		Response const& GetResponse();

	private:
		NginxConfig*	_config;
		Request*		_request;
		Response		_response;
		FileHandler		_file_handler;

		void		AssignResponseResolvedPath(std::string const& path = std::string());

		// Error page handling
		std::string FindCustomErrorPage(int error_code);
		void		HandleCustomError(std::string const& error_page_path);
		void		HandleDefaultError(int error_code);

		// Redirection
		bool		IsRedirected();
		void		HandleRedirection();

		// File handling
		void		ExecuteGet(bool set_code = true);

		// Response forming
		void		FormResponse();
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
