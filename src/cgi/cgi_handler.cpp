#include "cgi_handler.hpp"

CGIHandler::CGIHandler() : _cgi(CGI()) {}

size_t 		CGIHandler::execute(Request *request, Response *response) {
	if (_cgi.setup(request) == false) {
		response->SetStatusCode(_cgi.GetStatusCode());
		return _cgi.GetStatusCode();
	}
	_cgi.execute();
	response->SetStatusCode(_cgi.GetStatusCode());
	return _cgi.GetStatusCode();
}

std::string	CGIHandler::GetContent() const {
	return _cgi.getContent();
}