#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <queue>
#include "request.hpp"

class	RequestHandler {
	public:
		typedef std::queue<Request>	RequestQueue;

		// Default constructor
		RequestHandler();
		// Config file constructor
		explicit RequestHandler(NginxConfig* config);
		// Destructor
		~RequestHandler();

		size_t		Parse(char const* buffer);

	private:
		NginxConfig*	_config;
		Request*		_cur_request;
		// Request			_request;
		RequestQueue	_requests;
};

#endif /* REQUEST_HANDLER_HPP */
