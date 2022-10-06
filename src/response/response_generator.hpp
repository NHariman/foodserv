#ifndef RESPONSE_GENERATOR_HPP
#define RESPONSE_GENERATOR_HPP

#include "response.hpp"
#include "../request/request.hpp"

class ResponseGenerator {
	public:
		// Default constructor
		ResponseGenerator();
		// Destructor
		~ResponseGenerator();

		void	FormResponse(Response& response, Request* request);

	private:
		Response*	_response;
		Request*	_request;

		void				SetStatusLine();
		void				SetHeaders();
		void				SetDate();
		void				SetServer();
		void				SetLocation();
		void				SetContentType();
		void				SetContentLength();
		void				SetConnection();
		void				SetAllow();
		std::string			GetAllowedMethodsString();
};

#endif /* RESPONSE_GENERATOR_HPP */
