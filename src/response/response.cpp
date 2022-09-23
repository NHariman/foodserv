#include "response.hpp"

// Default constructor
Response::Response() : AHTTPMessage(), _stream(NULL), _complete(false) {}

// Assignment operator
Response&	Response::operator=(Response const& other) {
	if (this != &other) {
		_stream = new std::ifstream(other._resolved_path);
		_reason_phrase = other._reason_phrase;
		_resolved_path = other._resolved_path;
		_complete = other._complete;
		AHTTPMessage::operator=(other);
	}
	return *this;
}

// Destructor
Response::~Response() {
	if (_stream != NULL)
		delete _stream;
}


std::string const&	Response::GetReasonPhrase() const {
	return _reason_phrase;
}

void	Response::SetReasonPhrase(std::string const& phrase) {
	_reason_phrase = phrase;
}

std::istream*	Response::GetFileStream() const {
	return _stream;
}

void	Response::SetFileStream(std::istream* stream) {
	_stream = stream;
}

std::string const&	Response::GetResolvedPath() const {
	return _resolved_path;
}

void	Response::SetResolvedPath(std::string const& path) {
	_resolved_path = path;
}

bool	Response::IsComplete() const {
	return _complete;
}

// Takes optional argument to toggle bool to something other than true.
void	Response::SetComplete(bool value) {
	_complete = value;
}

std::istream*	Response::GetCompleteResponse() const {
	// create new stream pointer object of status line + file
}
