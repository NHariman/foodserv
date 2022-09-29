#include "cgi_handler.hpp"

CGIHandler::CGIHandler() : _cgi(CGI()) {}

// executes the CGI, sets the headers in the response class
// takes the remaining body and converts it to an istream for further use
// also sets status to 200 if it all went well, if not, it CGI would throw
std::istream* 		CGIHandler::execute(Request *request, Response *response) {
	size_t	header_bytes;
	std::string body;

	executeCGI(request);
	header_bytes = SetHeaders(response);
	body = RetrieveBody(header_bytes);
	_body = body; // delete later
	_content = CreateStreamFromString(body);
	if (!_content)
		throw CreateStreamFailureException("string");
	SetStatus(response); // sets response status code to 200 (anything else would throw)
	return _content;
}

void				CGIHandler::executeCGI(Request *request) {
	_cgi.setup(request);
	_cgi.execute();
}

size_t				CGIHandler::SetHeaders(Response *response) {
	HeaderFieldParser	_headers;
	return _headers.Parse(*response, _cgi.getContent());
}

std::string			CGIHandler::RetrieveBody(size_t start) {
	std::string body = _cgi.getContent().substr(start, _cgi.getContent().size() - start);
	return (body);
}

void				CGIHandler::SetStatus(Response *response) {
	response->SetStatusCode(200);
}

std::string			CGIHandler::GetContent() const {
	return _cgi.getContent();
}

std::string			CGIHandler::GetBody() const {
	return _body;
}
