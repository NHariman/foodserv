#include "location_uri.hpp"

LocationUri::LocationUri() : _uri("/"), _is_directory(true) {};

LocationUri::LocationUri(std::string input) : _uri(input) {
	if (input.compare("") == 0)
		throw MissingArgumentsException();
	if (IsUri(input) == false)
		throw BadUriException(input);
	if (input[input.size() - 1] == '/')
		_is_directory = true;
	else
		_is_directory = false;
}

LocationUri::LocationUri(LocationUri const &obj) :
	_uri(obj._uri),
	_is_directory(obj._is_directory) {}

LocationUri&	LocationUri::operator=(LocationUri const &obj) {
	if (this == &obj)
		return (*this);
	_uri = obj._uri;
	_is_directory = obj._is_directory;
	return (*this);
}

std::string				LocationUri::GetUri() const {
	return _uri.GetParsedURI();
}

URI				LocationUri::GetURIClass() const {
	return _uri;
}

bool			LocationUri::IsDirectory() const {
	return _is_directory;
}
