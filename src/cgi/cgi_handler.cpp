#include "cgi_handler.hpp"

CGIHandler::CGIHandler() : _cgi(CGI()) {}

CGIHandler::CGIHandler(Request *request) : _cgi(CGI()) {
	if (_cgi.setup(request) == false) {
		request->SetStatusCode(501);
		return ;
	}
	if (_cgi.execute() > 0) {
		request->SetStatusCode(501);
	}
	else {
		request->SetStatusCode(200);
	}
}

std::string	CGIHandler::GetContent() const {
	return _cgi.getContent();
}

void    execute_cgi(Request *request) {
	CGI cgi;

	if (cgi.setup(request) == false) {
		request->SetStatusCode(501);
		return ;
	}
	if (cgi.execute() > 0) {
		request->SetStatusCode(501);
	}
	else {
		request->SetStatusCode(200);
	}
	// convert cgi.getcontent() into filestream here?
}