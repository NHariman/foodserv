#include "response.hpp"
#include "../utils/utils.hpp"

// Default constructor
Response::Response() : HTTPMessage(), _body_stream(NULL), _send_stream(NULL), _complete(false) {}

// Assignment operator
Response&	Response::operator=(Response const& other) {
	if (this != &other) {
		_body_stream = new std::ifstream(other._resolved_path);
		_send_stream = other._send_stream;
		_reason_phrase = other._reason_phrase;
		_request_target	= other._request_target;
		_resolved_path = other._resolved_path;
		_complete = other._complete;
		HTTPMessage::operator=(other);
	}
	return *this;
}

// Destructor
Response::~Response() {
	if (_body_stream != NULL)
		delete _body_stream;
	if (_send_stream != NULL)
		delete _send_stream;
}

bool	Response::IsComplete() const {
	return _complete;
}

std::string const&	Response::GetReasonPhrase() const {
	return _reason_phrase;
}

void	Response::SetReasonPhrase(std::string const& phrase) {
	_reason_phrase = phrase;
}

std::istream*	Response::GetBodyStream() const {
	return _body_stream;
}

void	Response::SetBodyStream(std::istream* stream) {
	_body_stream = stream;
}

std::string const&	Response::GetRequestTarget() const {
	return _request_target;
}

void	Response::SetRequestTarget(std::string const& path) {
	_request_target = path;
}

std::string const&	Response::GetResolvedPath() const {
	return _resolved_path;
}

void	Response::SetResolvedPath(std::string const& path) {
	_resolved_path = path;
}

// Takes optional argument to toggle bool to something other than true.
void	Response::SetComplete(bool value) {
	_complete = value;
}

std::string	Response::GetFieldsAsString() const {
	std::string field_string;

	for (auto it = _header_fields.begin(); it != _header_fields.end(); it++) {
		field_string += it->first + ": " + it->second + "\r\n";
	}
	return field_string;
}

// Creates a stringstream object with append mode so output operations write
// to the end of stream.
// Combines response status line and body stream into a single stream for sending.
// If _send_stream is already initialized, simply returns the stream.
std::istream*	Response::GetCompleteResponse() {
	if (_send_stream == NULL) {
		std::iostream* complete_stream = new std::stringstream(std::ios_base::in | std::ios_base::out);
		std::string status_line = _http_version + " " + std::to_string(_status_code)
			+ " " + _reason_phrase + "\r\n";
		*complete_stream << status_line;
		*complete_stream << GetFieldsAsString() + "\r\n";
		if (_body_stream != NULL)
			*complete_stream << _body_stream->rdbuf();
		_send_stream = complete_stream;
	}
	return _send_stream;
}
#include <string.h>
std::string&	Response::GetCompleteResponseString() {
	if (_send_buffer.empty()) {
		std::string status_line = _http_version + " " + std::to_string(_status_code)
			+ " " + _reason_phrase + "\r\n";
		_send_buffer.append(status_line);
		_send_buffer.append(GetFieldsAsString() + "\r\n");
		std::cout << "send_buf: [" << _send_buffer << "]\n";
		std::cout << "size before body: " << _send_buffer.size() << std::endl;
		if (_body_stream != NULL) {
			// size_t body_size = GetStreamSize(_body_stream);
			// std::cout << "body size: " << body_size << std::endl;
			char read_buf[4096];
			// _send_buffer.append(_body_stream->rdbuf());
			while (_body_stream->read(read_buf, sizeof(read_buf)))
				_send_buffer.append(read_buf, sizeof(read_buf));
			_send_buffer.append(read_buf, _body_stream->gcount());

			if (_body_stream->bad())
				std::cerr << "Reading failed\n";
			// std::cout << "Bytes read: " << _body_stream->gcount() << std::endl;
			// std::cout << "read_buf size: " << strlen(read_buf) << std::endl;
			// read_buf[body_size] = '\0';
			// std::cout << "read_buf size: " << strlen(read_buf) << std::endl;
			// try {
			// 	_send_buffer.append(read_buf);
			// }
			// catch (...) {
			// 	std::cerr << "appending body failed\n";
			// }
		}
		std::cout << "size after body: " << _send_buffer.size() << std::endl;
	}
	return _send_buffer;
}
