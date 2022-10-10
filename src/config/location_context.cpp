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
{}

LocationContext::LocationContext(std::string data) : 
bool_uri(false),
bool_cgi_pass(false),
bool_allowed_methods(false),
bool_alias(false),
_location_uri(LocationUri()),
_cgi_pass(CGIPass()),
_allowed_methods(AllowedMethods()) {
    GetDirectiveValuePairs(data);
}

LocationContext& LocationContext::operator= (LocationContext const& location_context) {
    if (this == &location_context) {
        return (*this);
	}
	CopyValues(location_context);
    return (*this);
}

void							LocationContext::SetValue(int directive, std::string input) {
	std::string		value;

	value = TrimValue(input);

	if (DEBUG) std::cerr << "location context:\ndirective: " << directive << "\nvalue: " << value << std::endl;
	if (directive == 9) {
		SetURI(value);
	}
	else {
		switch(directive) {
			case 0: {
				if (bool_autoindex == true)
					throw MultipleAutoindexException(_location_uri.GetURIClass().GetInputURI());
				return SetAutoindexDir(value);
			}
			case 1: {
				if (bool_root == true)
					throw MultipleRootException(_location_uri.GetURIClass().GetInputURI());
				if (bool_alias == true)
					throw RootAndAliasException(_location_uri.GetURIClass().GetInputURI());
				return SetRoot(value);
			}
			case 2: {
				if (bool_index == true)
					throw MultipleIndexException(_location_uri.GetURIClass().GetInputURI());
				return SetIndex(value);
			}
			case 3: {
				if (bool_client_max_body_size == true)
					throw MultipleClientMaxBodySizeException(_location_uri.GetURIClass().GetInputURI());
				return SetCMBS(value);
			}
            case 4: {
				return SetErrorPage(value);
			}
            case 5: {
				if (bool_cgi_pass == true)
					throw MultipleCGIPassException(_location_uri.GetURIClass().GetInputURI());
				return SetCGI(value);
			}
            case 6: {
				if (bool_allowed_methods == true)
					throw MultipleAllowedMethodsException(_location_uri.GetURIClass().GetInputURI());
				return SetAllowedMethods(value);
			}
            case 7: {
				if (bool_return_dir == true)
					throw MultipleReturnException(_location_uri.GetURIClass().GetInputURI());
				return SetReturn(value);
			}
            case 8: {
				if (bool_alias == true)
					throw MultipleAliasException(_location_uri.GetURIClass().GetInputURI());
				if (bool_root == true)
					throw RootAndAliasException(_location_uri.GetURIClass().GetInputURI());
				return SetAlias(value);
			}
		}
	}
}

void							LocationContext::GetDirectiveValuePairs(std::string data) {
    size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					directive = 0;
    int                 i = 0;
    
    while (data[i] != '}') {
		key_start = data.find_first_not_of(" \t\n\v\f\r", i);
		if (data[key_start] == '}' || key_start == std::string::npos) {
			break ;
		}
		key_end = data.find_first_of(" \t\n\v\f\r", key_start);
		directive = IsDirective(data.substr(key_start, key_end - key_start));
		value_end = FindValue(directive, data, key_start, key_end);
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

#undef DEBUG