#include "location_uri.hpp"

LocationUri::LocationUri() : _is_empty(true) {};

LocationUri::LocationUri(std::string input) : _uri(input) {
	if (input.compare("") == 0)
		throw MissingArgumentsException();
	if (IsUri(input) == false)
		throw BadUriException();
	if (input[input.size() - 1] == '/')
		_is_directory = true;
	else
		_is_directory = false;
	_is_empty = false;
}

LocationUri::LocationUri(LocationUri const &obj) {
	_uri = obj.GetUri();
	_is_directory = obj.IsDirectory();
}

LocationUri&	LocationUri::operator=(LocationUri const &obj) {
	if (this == &obj)
		return (*this);
	_uri = obj.GetUri();
	_is_directory = obj.IsDirectory();
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

bool			LocationUri::IsEmpty() const {
	return _is_empty;
}
