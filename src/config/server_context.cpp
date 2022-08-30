/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_context.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 18:21:31 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/17 17:09:10 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server_context.hpp"
# include <algorithm>
# include "directive_validation/directive_validation.hpp"

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

ServerContext::ServerContext(size_t *start, std::string config_file, size_t server_nb) : _server_nb(server_nb) {
	InitChecklist();
	GetDirectiveValuePairs(start, config_file);
}

ServerContext::ServerContext() {
	InitChecklist();
}

ServerContext::ServerContext(const ServerContext& obj) : 	
	ConfigValues(obj), 
	amount_location_context(obj.amount_location_context),
	bool_listen(obj.bool_listen),
	bool_server_name(obj.bool_server_name),
	_server_nb(obj._server_nb),
	_location_contexts(obj._location_contexts),	
	_listen(obj._listen),
	_server_name(obj._server_name) {}

ServerContext & ServerContext::operator=(const ServerContext& obj) {
    if (this == &obj) {
        return (*this);
	}
    amount_location_context = obj.amount_location_context;
	bool_listen = obj.bool_listen;
	bool_server_name = obj.bool_server_name;
	bool_root = obj.bool_return_dir;
	bool_index = obj.bool_index;
	bool_client_max_body_size = obj.bool_client_max_body_size;
	bool_error_page = obj.bool_error_page;
	bool_autoindex = obj.bool_autoindex;
	bool_return_dir = obj.bool_return_dir;
	_location_contexts = obj._location_contexts;
	_listen = obj._listen;
	_server_name = obj._server_name;
	_root = obj._root;
	_index = obj._index;
	_client_max_body_size = obj._client_max_body_size;
	_error_page = obj._error_page;
	_autoindex = obj._autoindex;
	_return_dir = obj._return_dir;
	_server_nb = obj._server_nb;

	return (*this);
}

void		ServerContext::InitChecklist() {
    amount_location_context = 0;
	bool_listen = false;
	bool_server_name = false;
	bool_root = false;
	bool_index = false;
	bool_client_max_body_size = false;
	bool_error_page = false;
}

// compares found directive with possible directive values and either returns the number in the list
// or throws an error because a bad directive has been found
int			ServerContext::IsDirective(std::string directive){
	const std::string	directives[] = {"location", "listen", "server_name", "root", "index", "client_max_body_size", "error_page", "autoindex", "return"};
	
	int	is_directive = std::find(directives, directives + 9, directive) - directives;
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveException(directive, _server_nb);
	else
		return (is_directive);
}

// sets the value in the right directive within the server class based off the IsDirective return value
void				ServerContext::SetValue(int directive, std::string value){
	std::string		trimmed_value;

	trimmed_value = TrimValue(value);
	if (DEBUG) std::cerr << "server context:\ndirective: " << directive << "\nvalue: " << trimmed_value << std::endl;

	if (directive == 0) {
		amount_location_context++;
		LocationContext	location(trimmed_value);
		for (size_t i = 0 ; i < _location_contexts.size(); ++i){
			if (_location_contexts[i].GetLocationUri().GetUri().compare(location.GetLocationUri().GetUri()) == 0)
			throw DuplicateLocationUriException(_server_nb, _location_contexts[i].GetLocationUri().GetUri());
		}
		_location_contexts.push_back(location);
	}
	else {
		switch(directive) {
			case 1: {
				if (bool_listen == true)
					throw MultipleListensException(_server_nb);
				bool_listen = true;
				Listen	listen_port_ip(trimmed_value);
				_listen.first = listen_port_ip.getIpNumber();
				_listen.second = listen_port_ip.getPortNumber();
				break ;
			}
			case 2: {
				// TODO: still check these
				if (bool_server_name == true)
					throw MultipleServerNameException(_server_nb);
				bool_server_name = true;
				ServerName	server_name(trimmed_value);
				_server_name = server_name.GetServerNames();
				break ;
			}
			case 3: {
				if (bool_root == true)
					throw MultipleRootException(_server_nb);
				bool_root = true;
				Root	root_value(trimmed_value);
				_root = trimmed_value; // create a root class and use the GetRoot() function in there to paste root here if valid
				break ;
			}
			case 4:{
				if (bool_index == true)
					throw MultipleIndexException(_server_nb);
				bool_index = true;
				Index	index_value(trimmed_value);
				_index = index_value.GetIndex(); // create an index class and use the GetIndex() function in there to paste index here if valid
				break ;
			}
			case 5:{
				if (bool_client_max_body_size == true)
					throw MultipleClientMaxBodySizeException(_server_nb);
				bool_client_max_body_size = true;
				ClientMaxBodySize	cmbs_value(trimmed_value);
				_client_max_body_size = cmbs_value.GetValue();
				break ;
			}
			case 6:{
				bool_error_page = true;
				ErrorPage	error_page_value(trimmed_value);
				_error_page.push_back(error_page_value);
				break ;
			}
			case 7: {
				if (bool_autoindex == true)
					throw MultipleAutoindexException(_server_nb);
				bool_autoindex = true;
				Autoindex	autoindex_value(trimmed_value);
				_autoindex = autoindex_value.GetStatus();
				break ;
			}
            case 8: {
				if (bool_return_dir == true)
					throw MultipleReturnException(_server_nb);
				bool_return_dir = true;
				ReturnDir		return_dir_value(trimmed_value);
				_return_dir = return_dir_value;
				break ;
			}
		}
	}
	return ;
}

// checks if the necessary blocks have been set and otherwise prints a warning
// if something MUST be set, we should throw an exception
void			ServerContext::CheckListVerification(){
	if (amount_location_context > 0) {
		LocationContext default_location;
		_location_contexts.push_back(default_location);
		std::cerr << "WARNING! No location context detected in server context no." + std::to_string(_server_nb) + " Default have been set." << std::endl;
	}
	if (bool_listen == false) {
		_listen.first = 80;
		_listen.second = 0;
		std::cerr << "WARNING! No listen detected in server context no." + std::to_string(_server_nb) + " Defaults (80) have been set." << std::endl;
	}
	if (bool_server_name == false) {
		_server_name.push_back("localhost");
		std::cerr << "WARNING! No server_name detected in server context no." + std::to_string(_server_nb) + " Default (localhost) have been set." << std::endl;
	}
	if (bool_root == false) {
		_root = "/var/www/html";
		std::cerr << "WARNING! No server root detected in server context no." + std::to_string(_server_nb) + " Default (/var/www/html) have been set." << std::endl;
	}
	if (bool_index == false) {
		Index	input_value("index.php index.html index.htm index.nginx-debian.html");
		_index = input_value.GetIndex();
		std::cerr << "WARNING! No server index detected in server context no." + std::to_string(_server_nb) + " Default (index.php index.html index.htm index.nginx-debian.html) have been set." << std::endl;}
	if (bool_client_max_body_size == false) {
		_client_max_body_size = 1;
		std::cerr << "WARNING! No client_max_body_size detected in server context no." + std::to_string(_server_nb) + " Default (1mb) has been set." << std::endl;
	}
	if (bool_error_page == false) {
		// hardcoded error pages are used instead?
		std::cerr << "WARNING! No error_page detected in server context no." + std::to_string(_server_nb) + " Default have been set." << std::endl;
	}
	if (bool_autoindex == false) {
		_autoindex = false;
		std::cerr << "WARNING! No error_page detected in server context no." + std::to_string(_server_nb) + " Default have been set." << std::endl;
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
	int					ret;

	while (config_file[i] != '}') {
		key_start = config_file.find_first_not_of(" \t\n\v\f\r", i);
		if (config_file[key_start] == '}' || key_start == std::string::npos) {
			i = key_start;
			break ;
		}
		key_end = config_file.find_first_of(" \t\n\v\f\r", key_start);
		ret = IsDirective(config_file.substr(key_start, key_end - key_start));
		if (ret == 0) {
			value_end = FindLocationContextEnd(config_file, key_end);
			SetValue(ret, config_file.substr(key_end, value_end - key_end + 1));
		}
		else {
			value_end = config_file.find_first_of(';', key_end);
			SetValue(ret, config_file.substr(key_end, value_end - key_end));
		}
		if (value_end != std::string::npos)
			i = value_end + 1;
	}
	*start_position = i;
}

// check if is set
bool						ServerContext::IsSet(std::string directive) {
	const std::string	directives[] = {"location_context", "listen", "server_name", "root", "index", "client_max_body_size", "error_page", "autoindex", "return"};

	int	is_directive = std::find(directives, directives + 9, directive) - directives;
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveSetCheckException(_server_nb, directive);
	switch (is_directive) {
		case 0:
			return amount_location_context;
		case 1:
			return bool_listen;
		case 2:
			return bool_server_name;
		case 3:
			return bool_root;
		case 4:
			return bool_index;
		case 5:
			return bool_client_max_body_size;
		case 6:
			return bool_error_page;
		case 7:
			return bool_autoindex;
		case 8:
			return bool_return_dir;
	}
	throw InvalidDirectiveException(directive, _server_nb);
}

//getters
std::vector<LocationContext>	ServerContext::GetLocationContexts() const {
    return _location_contexts;
}

std::pair<in_addr_t, int>	ServerContext::GetListen() const {
    return _listen;
}

in_addr_t					ServerContext::GetIPAddress() const {
	return _listen.first;
}

int							ServerContext::GetPortNumber() const {
	return _listen.second;
}

std::vector<std::string>	ServerContext::GetServerNameVector() const {
    return _server_name;
}

std::vector<ErrorPage>		ServerContext::GetErrorPage() const {
	if (bool_error_page == false)
		throw DirectiveNotSetException("error_page", _server_nb);
    return _error_page;
} 

#undef DEBUG