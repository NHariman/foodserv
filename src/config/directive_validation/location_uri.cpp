#include "location_uri.hpp"
#include "../../utils.hpp"

LocationUri::LocationUri() : _is_empty(true) {};

LocationUri::LocationUri(std::string input) {
	if (input.compare("") == 0)
		throw MissingArgumentsException();
	if (IsUri(input) == false)
		throw BadUriException();
	if (input[input.size() - 1] == '/')
		_is_directory = true;
	else
		_is_directory = false;
	_uri = input;
	_is_empty = false;
	// validate uri through michelle's class.
}

LocationUri::LocationUri(LocationUri &obj) {
	_uri = obj.GetUri();
	_is_directory = obj.IsDirectory();
}

LocationUri&    LocationUri::operator=(LocationUri const &obj) {
	if (this == &obj)
		return (*this);
	_uri = obj.GetUri();
	_is_directory = obj.IsDirectory();
	return (*this);
}

std::string     LocationUri::GetUri() const {
	return _uri;
}

bool            LocationUri::IsDirectory() const {
	return _is_directory;
}

bool            LocationUri::IsEmpty() const {
	return _is_empty;
}
