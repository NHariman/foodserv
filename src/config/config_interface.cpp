#include "config_interface.hpp"

ConfigValues::ConfigValues() : bool_root(false),
bool_index(false),
bool_client_max_body_size(false),
bool_error_page(false),
bool_autoindex(false),
bool_return_dir(false) {}

ConfigValues::ConfigValues(const ConfigValues& obj) : bool_root(obj.bool_root),
bool_index(obj.bool_index),
bool_client_max_body_size(obj.bool_client_max_body_size),
bool_error_page(obj.bool_error_page),
bool_autoindex(obj.bool_autoindex),
bool_return_dir(obj.bool_return_dir),
_root(obj._root),
_index(obj._index),
_client_max_body_size(obj._client_max_body_size),
_error_page(obj._error_page),
_autoindex(obj._autoindex),
_return_dir(obj._return_dir) {}


ConfigValues&	ConfigValues::operator=(const ConfigValues& obj) {
	if (this == &obj)
		return (*this);
	bool_index = obj.bool_index;
	bool_client_max_body_size = obj.bool_client_max_body_size;
	bool_error_page = obj.bool_error_page;
	bool_autoindex = obj.bool_autoindex;
	bool_return_dir = obj.bool_return_dir;
	_root = obj._root;
	_index = obj._index;
	_client_max_body_size = obj._client_max_body_size;
	_error_page = obj._error_page;
	_autoindex = obj._autoindex;
	_return_dir = obj._return_dir;
	return (*this);
}

std::string					ConfigValues::GetRoot() const {
    return _root;
}

std::vector<std::string>	ConfigValues::GetIndex() const {
    return _index;
}

size_t						ConfigValues::GetClientMaxBodySize() const {
    return _client_max_body_size;
}

bool						ConfigValues::GetAutoindex() const {
	return _autoindex;
}

ReturnDir					ConfigValues::GetReturn() const {
	return _return_dir;
}

bool						ConfigValues::HasErrorPage() const {
	return bool_error_page;
}

std::vector<ErrorPage>		ConfigValues::GetErrorPage() const {
    return _error_page;
}