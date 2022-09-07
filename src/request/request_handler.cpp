#include "request_handler.hpp"

// Default constructor
RequestHandler::RequestHandler() {}

// Config file constructor
RequestHandler::RequestHandler(NginxConfig* config)
	:  _config(config), _cur_request(NULL) {}//, _request(config) {}

// Destructor
RequestHandler::~RequestHandler() {}

size_t	RequestHandler::Parse(char const* buffer) {
	// if (_cur_request == NULL) {
	// 	_cur_request = new Request(_config);
	// }
	Request request(_config);
	size_t	ret;

	ret = request.Parse(buffer);
	if (request.GetStatus() == Request::Status::Complete)
		_requests.push(request);
	return ret;
}