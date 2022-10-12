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

void				LocationContext::SetLocationAutoindexDir(std::string value){ConfigValues::SetAutoindexDir(value);}
void				LocationContext::SetLocationRoot(std::string value){ConfigValues::SetRoot(value);}
void				LocationContext::SetLocationIndex(std::string value){ConfigValues::SetIndex(value);}
void				LocationContext::SetLocationCMBS(std::string value){ConfigValues::SetCMBS(value);}
void				LocationContext::SetLocationErrorPage(std::string value){ConfigValues::SetErrorPage(value);}
void				LocationContext::SetLocationReturn(std::string value){ConfigValues::SetReturn(value);}

void							LocationContext::SetValue(int const directive, std::string input) {
	std::string		value;

	void (LocationContext::*set_directive[])(std::string) = {
		&LocationContext::SetLocationAutoindexDir,
		&LocationContext::SetLocationRoot,
		&LocationContext::SetLocationIndex,
		&LocationContext::SetLocationCMBS,
		&LocationContext::SetLocationErrorPage,
		&LocationContext::SetCGI,
		&LocationContext::SetAllowedMethods,
		&LocationContext::SetLocationReturn,
		&LocationContext::SetAlias,
		&LocationContext::SetURI,
		nullptr
	};

	value = TrimValue(input);
	if (DEBUG) std::cerr << "location context:\ndirective: " << directive << "\nvalue: " << value << std::endl;
	DoubleDirectiveCheck(directive);
	(this->*set_directive[directive])(value);

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