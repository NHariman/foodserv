#include "config_interface.hpp"

/*
        bool	bool_root;
	    bool	bool_index;
	    bool	bool_client_max_body_size;
	    bool	bool_error_page;
	    bool	bool_autoindex;
	    bool	bool_return_dir;

        std::string						_root;
		std::vector<std::string>		_index;
		size_t							_client_max_body_size;
		std::map<int, std::string>		_error_page;
		bool							_autoindex;
		ReturnDir						_return_dir;
*/

ConfigValues::ConfigValues() : 
bool_root(false),
bool_index(false),
bool_client_max_body_size(false),
bool_error_page(false),
bool_autoindex(false),
bool_return_dir(false),
_root("/www/html"),
_client_max_body_size(1),
_error_page(),
_autoindex(false),
_return_dir(ReturnDir()) {
		Index	input_value("index.php index.html index.htm index.nginx-debian.html");
		_index = input_value.GetIndex();
}

ConfigValues::ConfigValues(const ConfigValues& obj) : 
bool_root(obj.bool_root),
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

std::map<int, std::string>		ConfigValues::GetErrorPage() const {
    return _error_page;
}

void    ConfigValues::SetRoot(std::string trimmed_value) {
	bool_root = true;
	_root.clear();
	Root	root_value(trimmed_value);
	_root = trimmed_value;
}

void    ConfigValues::SetIndex(std::string trimmed_value) {
	bool_index = true;
	_index.clear();
	Index	index_value(trimmed_value);
	_index = index_value.GetIndex();
}

void    ConfigValues::SetCMBS(std::string trimmed_value) {
	bool_client_max_body_size = true;
	ClientMaxBodySize	cmbs_value(trimmed_value);
	_client_max_body_size = cmbs_value.GetValue();
}

void    ConfigValues::SetErrorPage(std::string trimmed_value) {
	bool_error_page = true;
	AddToErrorPageMap(&_error_page, trimmed_value);
}

void    ConfigValues::SetAutoindexDir(std::string trimmed_value) {
	bool_autoindex = true;
	_autoindex = SetAutoindex(trimmed_value);
}

void    ConfigValues::SetReturn(std::string trimmed_value) {
	bool_return_dir = true;
	ReturnDir		return_dir_value(trimmed_value);
	_return_dir = return_dir_value;
}

void	ConfigValues::AddToErrorPageMap(std::map<int, std::string> *map, std::string input) {
	int code;

	if (input.compare("") == 0)
		throw ErrorPage::MissingArgumentsException();

	std::vector<std::string> items = ToStringVector(input);

	std::string uri = items[items.size() - 1];
	if (IsUri(uri) == false)
		throw ErrorPage::BadErrorURIException();
	for (size_t i = 0; i < (items.size() - 1); ++i) {
		if (IsNumber(items[i]) == true) {
			code = std::atoi(items[i].c_str());
			if (code < 300 || code > 599)
				throw ErrorPage::BadErrorCodeException();
			std::map<int,std::string>::iterator it = map->find(code);
			if (it == map->end())
				map->insert(std::pair<int, std::string> (code, uri));
			else
				throw ErrorPage::DuplicateErrorCodeException();
		}
		else
			throw ErrorPage::InvalidCodeInputException();
	}
}

void	ConfigValues::PrintErrorPage() const {
	for(std::map<int, std::string>::const_iterator it = _error_page.begin();
		it != _error_page.end(); ++it){
		std::cout << it->first << " " << it->second << "\n";
	}
}