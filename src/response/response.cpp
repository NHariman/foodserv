#include "response.hpp"

// Default constructor
Response::Response() : AHTTPMessage(), _file(NULL), _complete(false) {}

// Destructor
Response::~Response() {}


std::string const& Response::GetReasonPhrase() const {
	return _reason_phrase;
}

void Response::SetReasonPhrase(std::string const& phrase) {
	_reason_phrase = phrase;
}

std::fstream* Response::GetFileStream() const {
	return _file;
}

void Response::SetFileStream(std::fstream* file) {
	_file = file;
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
