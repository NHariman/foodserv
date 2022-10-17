#include "server_context.hpp"

ServerContext::ServerContext(size_t *start, std::string config_file, size_t server_nb) : 
_amount_location_context(0),
bool_listen(false),
bool_server_name(false),
_server_nb(server_nb),
_listen("80", "0")
{
	_location_contexts.push_back(LocationContext());
	_server_name.push_back("localhost");
	GetDirectiveValuePairs(start, config_file);
	if (HasLocation("/") == false) {
		LocationContext default_location;
		_amount_location_context++;
		_location_contexts.push_back(default_location);
	}
}

ServerContext::ServerContext():  
_amount_location_context(0),
bool_listen(false),
bool_server_name(false),
_server_nb(0),
_listen("80", "0")
{
	_location_contexts.push_back(LocationContext());
	_server_name.push_back("localhost");
}

ServerContext & ServerContext::operator=(const ServerContext& obj) {
    if (this == &obj) {
        return (*this);
	}
	CopyValues(obj);
	return (*this);
}

void					ServerContext::SetServerRoot(std::string value) {ConfigValues::SetRoot(value);}
void					ServerContext::SetServerIndex(std::string value) {ConfigValues::SetIndex(value);}
void					ServerContext::SetServerCMBS(std::string value) {ConfigValues::SetCMBS(value);}
void					ServerContext::SetServerErrorPage(std::string value) {ConfigValues::SetErrorPage(value);}
void					ServerContext::SetServerAutoindexDir(std::string value) {ConfigValues::SetAutoindexDir(value);}
void					ServerContext::SetServerReturn(std::string value) {ConfigValues::SetReturn(value);}

// sets the value in the right directive within the server class based off the IsDirective return value
void				ServerContext::SetValue(int directive, std::string value){
	std::string		trimmed_value;

	void (ServerContext::*set_directive[])(std::string) = {
		&ServerContext::SetLocation,
		&ServerContext::SetListen,
		&ServerContext::SetServerName,
		&ServerContext::SetServerRoot,
		&ServerContext::SetServerIndex,
		&ServerContext::SetServerCMBS,
		&ServerContext::SetServerErrorPage,
		&ServerContext::SetServerAutoindexDir,
		&ServerContext::SetServerReturn,
		nullptr
	};

	if (value.compare("") == 0)
		throw BadInputException(_server_nb);
	trimmed_value = TrimValue(value);
	DoubleDirectiveCheck(directive);
	(this->*set_directive[directive])(trimmed_value);

}

size_t						ServerContext::FindLocationContextEnd(std::string config_file, size_t start) {
	size_t i = start;
	size_t open_bracket = 0;
	
	while (config_file[i]) {
		if (config_file[i] == '{')
			open_bracket++;
		else if (config_file[i] == '}' && open_bracket > 0)
			open_bracket--;
		if (config_file[i] == '}' && open_bracket == 0)
			break ;
		i++;
	}
	return (i);
}

// starts after the { of the server{ 
// finds the directive and compares it with the possible directives.
// if the directive is deemed valid, it checks if a location context has been found
// if so, it grabs the location context to use by looking for the first available }
// otherwise it finds the ';' and sends that substring
// to SetValue, which sets the value in the right directive.
// this function keeps checking until the end of the ServerContext is reached.
void          ServerContext::GetDirectiveValuePairs(size_t *start_position, std::string config_file) {
	
    int					i = *start_position;
	size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					directive;

	while (config_file[i] != '}') {
		key_start = config_file.find_first_not_of(" \t\n\v\f\r", i);
		if (config_file[key_start] == '}' || key_start == std::string::npos) {
			i = key_start;
			break ;
		}
		key_end = config_file.find_first_of(" \t\n\v\f\r", key_start);
		directive = IsDirective(config_file.substr(key_start, key_end - key_start));
		i = FindValue(directive, config_file, key_end);
		if (value_end != std::string::npos)
			i++;
	}
	*start_position = i;
}



//getters
std::vector<LocationContext>		ServerContext::GetLocationContexts() const {
    return _location_contexts;
}

std::pair<std::string, std::string>	ServerContext::GetListen() const {
    return _listen;
}

std::string					ServerContext::GetIPAddress() const {
	return _listen.first;
}

std::string					ServerContext::GetPortNumber() const {
	return _listen.second;
}

std::vector<std::string>	ServerContext::GetServerNameVector() const {
    return _server_name;
}
