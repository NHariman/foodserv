#ifndef RESPONSE_HANDLER_HPP
#define RESPONSE_HANDLER_HPP

#include "request.hpp"
#include "response.hpp"

class ResponseHandler {
	public:
		// Default constructor
		ResponseHandler();
		// Destructor
		~ResponseHandler();

		void HandleError(Request& request);
		void HandleExpect(Request& request);
		void HandleRegular(Request& request);

	private:
		Response	_response;
};

#endif /* RESPONSE_HANDLER_HPP */
