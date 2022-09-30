#include "location_context.hpp"

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

void						LocationContext::SetAllowedMethods(std::string value) {
   	bool_allowed_methods = true;
	AllowedMethods allowed_methods_value(value);
	_allowed_methods = allowed_methods_value; 
}

void						LocationContext::SetAlias(std::string value) {
    Root alias_value(value);
	bool_alias = true;
	_alias = value;
}

void						LocationContext::SetCGI(std::string value) {
	bool_cgi_pass = true;
	CGIPass cgi_pass_value(value);
	_cgi_pass = value;
}

void                        LocationContext::SetURI(std::string value) {
 	bool_uri = true;
	LocationUri		uri_value(value);
	_location_uri = uri_value;
}

// finds the URI of the location context
size_t                        LocationContext::FindURI(int directive, std::string data, size_t key_start, size_t key_end) {
    size_t value_end;
	SetValue(directive, data.substr(key_start, key_end - key_start));
	value_end = data.find_first_of('{', key_end);
	return value_end;
}

// finds the values of the directives (pointed to by directive) within the location context
size_t                        LocationContext::FindValue(int directive, std::string data, size_t key_end) {
    size_t value_end;
	value_end = data.find_first_of(';', key_end);
	if (!HasContent(';', key_end, value_end, data))
		throw BadInputException(_location_uri.GetURIClass().GetInputURI());
	SetValue(directive, data.substr(key_end, value_end - key_end));
	return value_end;
}