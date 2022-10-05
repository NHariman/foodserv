#include "cgi_handler.hpp"

CGIHandler::CGIHandler() : _cgi(CGI()) {}

// executes the CGI, sets the headers in the response class
// takes the remaining body and converts it to an istream for further use
// also sets status to 200 if it all went well, if not, it CGI would throw
std::istream* 		CGIHandler::Execute(Request *request, Response *response) {
	size_t	header_bytes;
	std::string body;

	try {
		ExecuteCGI(request);
		header_bytes = SetHeaders(response);
		body = RetrieveBody(header_bytes);
		_body = body; // delete later
		CreateBodyStream(body);
		SetStatus(response); // sets response status code to 200 (anything else would throw)
		return _content;
	}
	catch (InternalError::exception &e) {
		throw InternalServerErrorException();
	}
}

void				CGIHandler::CreateBodyStream(std::string body) {
	_content = CreateStreamFromString(body);
	if (!_content)
		throw CreateStreamFailureException("string");
}

void				CGIHandler::ExecuteCGI(Request *request) {
	_cgi.Setup(request);
	_cgi.Execute();
}

size_t				CGIHandler::SetHeaders(Response *response) {
	HeaderFieldParser	_headers;
	return _headers.Parse(*response, _cgi.GetContent());
}

std::string			CGIHandler::RetrieveBody(size_t start) {
	std::string body = _cgi.GetContent().substr(start, _cgi.GetContent().size() - start);
	return (body);
}

void				CGIHandler::SetStatus(Response *response) {
	response->SetStatusCode(200);
}

std::string			CGIHandler::GetContent() const {
	return _cgi.GetContent();
}

std::string			CGIHandler::GetBody() const {
	return _body;
}
