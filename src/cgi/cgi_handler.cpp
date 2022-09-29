#include "cgi_handler.hpp"

CGIHandler::CGIHandler() : _cgi(CGI()) {}

void 		CGIHandler::execute(Request *request, Response *response) {
	_cgi.setup(request);
	_cgi.execute();
	// use HeaderFieldParser to get the header, save the amounts parsed
	// trim the body down to only contain body content
	// convert body to std::istream
	// send std::istream of body back to michelle
	// set response status code
}

std::string	CGIHandler::GetContent() const {
	return _cgi.getContent();
}