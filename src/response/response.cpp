#include "response.hpp"

// Default constructor
Response::Response() : AHTTPMessage(), _stream(NULL), _complete(false) {}

// Destructor
Response::~Response() {
	if (_stream != NULL)
		delete _stream;
}


std::string const& Response::GetReasonPhrase() const {
	return _reason_phrase;
}

void Response::SetReasonPhrase(std::string const& phrase) {
	_reason_phrase = phrase;
}

std::istream* Response::GetFileStream() const {
	return _stream;
}

void Response::SetFileStream(std::istream* stream) {
	_stream = stream;
}

std::string const& Response::GetResolvedPath() const {
    return _resolved_path;
}

void Response::SetResolvedPath(std::string const& path) {
    _resolved_path = path;
}

bool Response::IsComplete() const {
	return _complete;
}
