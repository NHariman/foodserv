#include "location_context.hpp"

# define DEBUG 0

// use to check if a directive has been set
bool						LocationContext::IsSet(std::string directive) {
	int	is_directive = GetDirective(directive);
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

int							LocationContext::GetDirective(std::string directive) {
    const std::string	directives[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "cgi_pass", "allowed_methods", "return", "alias"};

    int	is_directive = std::find(directives, directives + 9, directive) - directives;
    return is_directive;
}

int								LocationContext::IsDirective(std::string directive) {
    if (bool_uri == false) {
		return 9;
	}
	int	is_directive = GetDirective(directive);
	if (is_directive < 0 || is_directive > 8){
		std::cout << "directive fail: " << directive << std::endl;
		throw InvalidDirectiveException(_location_uri.GetURIClass().GetInputURI(), directive);
	}
	else
		return (is_directive);
}

void                LocationContext::CopyValues(LocationContext const& location_context) {
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
}

#undef DEBUG