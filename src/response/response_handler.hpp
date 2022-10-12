#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include "response.hpp"
#include "file_handler.hpp"
#include "../err/error_responses.hpp"
#include "../request/request.hpp"

class ResponseHandler {
	public:

		// Default constructor
		ResponseHandler();
		// Destructor
		~ResponseHandler();

		bool	Ready();
		bool	IsDone() const;
		void	Send(int fd);
		void	HandleError(Request& request);
		void	HandleExpect(Request& request);
		void	HandleRegular(Request& request);

		Response const& GetResponse();

	private:
		Request*			_request;
		Response::pointer	_response;
		FileHandler			_file_handler;
		bool				_is_done;

		void				AssignResponseResolvedPath(std::string const& path = std::string());

		// Error page handling
		std::string 		FindCustomErrorPage(int error_code);
		void				HandleCustomError(std::string const& error_page_path);
		void				HandleDefaultError(int error_code);

		// Redirection
		bool				IsRedirected();
		void				HandleRedirection();

		// CGI
		bool				IsHandledByCGI();
		void				HandleCGI();

		// File handling
		void				HandleMethod();
		FileHandler::Method	DetermineMethod();

		// Make response
		void				FormResponse();
};

#endif /* RESPONSE_HANDLER_HPP */
