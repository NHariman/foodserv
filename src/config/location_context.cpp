#include "location_context.hpp"

#define DEBUG 0

LocationContext::LocationContext() :
bool_uri(false),
bool_cgi_pass(false),
bool_allowed_methods(false),
bool_alias(false),
_location_uri(LocationUri()),
_cgi_pass(CGIPass()),
_allowed_methods(AllowedMethods())
{
	InitChecklist();
	bool_autoindex = false;
	bool_root = false;
	bool_index = false;
	bool_client_max_body_size = false;
	bool_error_page = false;
	bool_return_dir = false;
}

LocationContext::LocationContext(std::string data) {
	InitChecklist();
    GetDirectiveValuePairs(data);
	CheckListVerification();
}

LocationContext& LocationContext::operator= (LocationContext const& location_context) {
    if (this == &location_context) {
        return (*this);
	}

	// bool
	bool_uri = location_context.bool_uri;
    bool_autoindex = location_context.bool_autoindex;
    bool_root = location_context.bool_root;
	bool_alias = location_context.bool_alias;
    bool_index = location_context.bool_index;
    bool_client_max_body_size = location_context.bool_client_max_body_size;
	bool_error_page = location_context.bool_error_page;
	bool_return_dir = location_context.bool_return_dir;
    bool_cgi_pass = location_context.bool_cgi_pass;
	bool_allowed_methods = location_context.bool_allowed_methods;

	// values
    _location_uri = location_context._location_uri;
    _autoindex = location_context._autoindex;
    _root = location_context._root;
	_alias = location_context._alias;
    _index = location_context._index;
	_return_dir = location_context._return_dir;
    _client_max_body_size = location_context._client_max_body_size;
	_error_page = location_context._error_page;
    _cgi_pass = location_context._cgi_pass;
	_allowed_methods = location_context._allowed_methods;

    return (*this);
}

LocationContext::LocationContext(LocationContext const& location_context) : ConfigValues(location_context),
bool_cgi_pass(location_context.bool_cgi_pass),
bool_allowed_methods(location_context.bool_allowed_methods),
bool_alias(location_context.bool_alias),
_location_uri(location_context._location_uri),
_cgi_pass(location_context._cgi_pass),
_allowed_methods(location_context._allowed_methods),
_alias(location_context._alias)
{}

void	LocationContext::InitChecklist() {
	bool_uri = false;
    bool_autoindex = false;
    bool_root = false;
    bool_index = false;
    bool_client_max_body_size = false;
	bool_error_page = false;
    bool_cgi_pass = false;
	bool_allowed_methods = false;
	bool_alias = false;
	bool_return_dir = false;
}

int								LocationContext::IsDirective(std::string directive) {
	const std::string	directives[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "cgi_pass", "allowed_methods", "return", "alias"};

    if (bool_uri == false) {
		return 9;
	}
	int	is_directive = std::find(directives, directives + 9, directive) - directives;
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveException(_location_uri.GetURIClass().GetInputURI(), directive);
	else
		return (is_directive);
}

void							LocationContext::SetValue(int directive, std::string input) {
	std::string		value;

	value = TrimValue(input);

	if (DEBUG) std::cerr << "location context:\ndirective: " << directive << "\nvalue: " << value << std::endl;

	if (directive == 9) {
		bool_uri = true;
		LocationUri		uri_value(value);
		_location_uri = uri_value;
	}
	else {
		switch(directive) {
			case 0: {
				if (bool_autoindex == true)
					throw MultipleAutoindexException(_location_uri.GetURIClass().GetInputURI());
				bool_autoindex = true;
				_autoindex = SetAutoindex(value);
				break ;
			}
			case 1: {
				if (bool_root == true)
					throw MultipleRootException(_location_uri.GetURIClass().GetInputURI());
				if (bool_alias == true)
					throw RootAndAliasException(_location_uri.GetURIClass().GetInputURI());
				bool_root = true;
				Root root_value(value);
				_root = value;
				break ;
			}
			case 2: {
				if (bool_index == true)
					throw MultipleIndexException(_location_uri.GetURIClass().GetInputURI());
				bool_index = true;
				Index	index_value(value);
				_index = index_value.GetIndex();
				break ;
			}
			case 3: {
				if (bool_client_max_body_size == true)
					throw MultipleClientMaxBodySizeException(_location_uri.GetURIClass().GetInputURI());
				bool_client_max_body_size = true;
				ClientMaxBodySize	cmbs_value(value);
				_client_max_body_size = cmbs_value.GetValue();
				break ;
			}
            case 4: {
				bool_error_page = true;
				AddToErrorPageMap(&_error_page, value);
				// ErrorPage	error_page_value(value);
				// _error_page.push_back(error_page_value);
				// if the same error is given twice, throw an error
				// change this to a map for easier handler
				break ;
			}
            case 5: {
				if (bool_cgi_pass == true)
					throw MultipleCGIPassException(_location_uri.GetURIClass().GetInputURI());
				bool_cgi_pass = true;
				CGIPass cgi_pass_value(value);
				_cgi_pass = value;
				break ;
			}
            case 6: {
				if (bool_allowed_methods == true)
					throw MultipleAllowedMethodsException(_location_uri.GetURIClass().GetInputURI());
				bool_allowed_methods = true;
				AllowedMethods allowed_methods_value(value);
				_allowed_methods = allowed_methods_value;
				break ;
			}
            case 7: {
				if (bool_return_dir == true)
					throw MultipleReturnException(_location_uri.GetURIClass().GetInputURI());
				bool_return_dir = true;
				ReturnDir		return_dir_value(value);
				_return_dir = return_dir_value;
				break ;
			}
            case 8: {
				if (bool_alias == true)
					throw MultipleAliasException(_location_uri.GetURIClass().GetInputURI());
				if (bool_root == true)
					throw RootAndAliasException(_location_uri.GetURIClass().GetInputURI());
				Root alias_value(value);
				bool_alias = true;
				_alias = value;
				break ;
			}
		}
	}
}

void							LocationContext::CheckListVerification(){
    if (bool_autoindex == false) {
		if (DEBUG) std::cerr << "WARNING! " + _location_uri.GetURIClass().GetInputURI() + " does not have an autoindex set. Default in Server context will be used." << std::endl;
	}
    if (bool_root == false) {
		if (DEBUG) std::cerr << "WARNING! " + _location_uri.GetURIClass().GetInputURI() + " does not have a root set. Default in Server context will be used." << std::endl;
	}
	if (bool_index == false) {
		if (DEBUG) std::cerr << "WARNING! " + _location_uri.GetURIClass().GetInputURI() + " does not have a index set. Default in Server context will be used." << std::endl;
	}
	if (bool_client_max_body_size == false) {
		if (DEBUG) std::cerr << "WARNING! " + _location_uri.GetURIClass().GetInputURI() + " does not have a client_max_body_size set. Default in Server context will be used." << std::endl;
	}
	if (bool_allowed_methods == false) {
		_allowed_methods = AllowedMethods();
		if (DEBUG) std::cerr << "WARNING! " + _location_uri.GetURIClass().GetInputURI() + " does not have a allowed_methods set. Default (No methods allowed) have been set." << std::endl;
	}
	if (bool_cgi_pass == false) {
		_cgi_pass = CGIPass();
	}
}

void							LocationContext::GetDirectiveValuePairs(std::string data) {
    size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					ret;
    int                 i = 0;
    
    while (data[i] != '}') {
		key_start = data.find_first_not_of(" \t\n\v\f\r", i);
		if (data[key_start] == '}' || key_start == std::string::npos) {
			break ;
		}
		key_end = data.find_first_of(" \t\n\v\f\r", key_start);
		ret = IsDirective(data.substr(key_start, key_end - key_start));
		if (ret == 9) {
            SetValue(ret, data.substr(key_start, key_end - key_start));
			value_end = data.find_first_of('{', key_end);
		}
		else {
            value_end = data.find_first_of(';', key_end);
			if (!HasContent(';', key_end, value_end, data))
				throw BadInputException(_location_uri.GetURIClass().GetInputURI());
		    SetValue(ret, data.substr(key_end, value_end - key_end));
        }
		if (value_end != std::string::npos)
			i = value_end + 1;
	}
}

// getters
LocationUri							LocationContext::GetLocationUri() const {
	return _location_uri;
}

std::string							LocationContext::GetAlias() const {
   return _alias;
}

CGIPass							LocationContext::GetCGIPass() const {
    return _cgi_pass;
}

AllowedMethods						LocationContext::GetAllowedMethods() const {
    return _allowed_methods;
}

std::string LocationUri::GetInputURI() const {
	return _uri.GetInputURI();
}

// use to check if a directive has been set
bool						LocationContext::IsSet(std::string directive) {
	const std::string	directives[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "cgi_pass", "allowed_methods", "return", "alias"};

	int	is_directive = std::find(directives, directives + 9, directive) - directives;
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveSetCheckException(_location_uri.GetURIClass().GetInputURI());
	switch (is_directive) {
		case 0:
			return bool_autoindex;
		case 1:
			return bool_root;
		case 2:
			return bool_index;
		case 3:
			return bool_client_max_body_size;
		case 4:
			return bool_error_page;
		case 5:
			return bool_cgi_pass;
		case 6:
			return bool_allowed_methods;
		case 7:
			return bool_return_dir;
		case 8:
			return bool_alias;
	}
	throw InvalidDirectiveException(_location_uri.GetURIClass().GetInputURI());
}

#undef DEBUG