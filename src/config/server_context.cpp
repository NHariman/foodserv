#include "server_context.hpp"

#define DEBUG 0

// error pages are hardcoded in the real nginx:
// static char ngx_http_error_404_page[] =
// "<html>" CRLF
// "<head><title>404 Not Found</title></head>" CRLF
// "<body>" CRLF
// "<center><h1>404 Not Found</h1></center>" CRLF
//;

// when to throw:
// when multiple listen blocks
// when multiple client_max_body_size
// when two location blocks have the same uri
// when multiple roots

ServerContext::ServerContext(size_t *start, std::string config_file, size_t server_nb) : 
ConfigValues(),
_amount_location_context(0),
bool_listen(false),
bool_server_name(false),
_server_nb(server_nb) {
	InitChecklist();

	GetDirectiveValuePairs(start, config_file);
	CheckListVerification();
}

ServerContext::ServerContext():  ConfigValues(),
_amount_location_context(0),
bool_listen(false),
bool_server_name(false),
_server_nb(1) {
	InitChecklist();
}

ServerContext & ServerContext::operator=(const ServerContext& obj) {
    if (this == &obj) {
        return (*this);
	}
	CopyValues(obj);
	return (*this);
}

void		ServerContext::InitChecklist() {
    _amount_location_context = 0;

	_root = "/var/www/html";
	_client_max_body_size = 1;
	_autoindex = false;
	_listen.first = "80";
	_listen.second = "0";
}

// sets the value in the right directive within the server class based off the IsDirective return value
void				ServerContext::SetValue(int directive, std::string value){
	std::string		trimmed_value;

	if (value.compare("") == 0)
		throw BadInputException(_server_nb);
	trimmed_value = TrimValue(value);
	if (DEBUG) std::cerr << "server context:\ndirective: " << directive << "\nvalue: " << trimmed_value << std::endl;
	if (directive == 0) {
		SetLocation(trimmed_value);
	}
	else {
		switch(directive) {
			case 1: {
				return SetListen(trimmed_value);
			}
			case 2: {
				return SetServerName(trimmed_value);
			}
			case 3: {
				if (bool_root == true)
					throw MultipleRootException(_server_nb);
				return SetRoot(trimmed_value);
			}
			case 4:{
				if (bool_index == true)
					throw MultipleIndexException(_server_nb);
				return SetIndex(trimmed_value);
			}
			case 5:{
				if (bool_client_max_body_size == true)
					throw MultipleClientMaxBodySizeException(_server_nb);
				return SetCMBS(trimmed_value);
			}
			case 6:{
				return SetErrorPage(trimmed_value);
			}
			case 7: {
				if (bool_autoindex == true)
					throw MultipleAutoindexException(_server_nb);
				return SetAutoindexDir(trimmed_value);
			}
            case 8: {
				if (bool_return_dir == true)
					throw MultipleReturnException(_server_nb);
				return SetReturn(trimmed_value);
			}
		}
	}
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
		if (directive == 0) {
			FindLocationContext(directive, config_file, &value_end, key_end);
		}
		else {
			FindValue(directive, config_file, &value_end, key_end);
		}
		if (value_end != std::string::npos)
			i = value_end + 1;
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

#undef DEBUG