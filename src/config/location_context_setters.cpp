#include "location_context.hpp"


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

size_t						LocationContext::FindValue(int directive, std::string data, size_t key_start, size_t key_end) {
	std::string input;
	size_t value_end;
	if (directive == 9) {
		input = data.substr(key_start, key_end - key_start);
		value_end = data.find_first_of('{', key_end);
	}
	else {
		value_end = data.find_first_of(';', key_end);
		if (!HasContent(';', key_end, value_end, data))
			throw BadInputException(_location_uri.GetURIClass().GetInputURI());
		input = data.substr(key_end, value_end - key_end);
	}
	SetValue(directive, input);
	return value_end;
}