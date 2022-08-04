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

ServerContext::ServerContext(size_t *start, std::string config_file) {

    // _check_list copy
    _check_list.location_context = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
	FindDirectiveValuePairs(start, config_file);
}

ServerContext::ServerContext() {
    // _check_list copy
    _check_list.location_context = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
}

ServerContext::ServerContext(const ServerContext& obj) {
	_location_contexts = obj.GetLocationContexts();
	_listen = obj.GetListen();
	_server_name = obj.GetServerNameVector();
	_root = obj.GetRoot();
	_index = obj.GetIndex();
	_client_max_body_size = obj.GetClientMaxBodySize();
	_error_page = obj.GetErrorPage();

    // _check_list copy
    _check_list.location_context = obj.GetFlags().location_context;
	_check_list.listen = obj.GetFlags().listen;
	_check_list.server_name = obj.GetFlags().server_name;
	_check_list.root = obj.GetFlags().root;
	_check_list.index = obj.GetFlags().index;
	_check_list.client_max_body_size = obj.GetFlags().client_max_body_size;
	_check_list.error_page = obj.GetFlags().error_page;
}

ServerContext & ServerContext::operator=(const ServerContext& obj) {
    if (this == &obj) {
        return (*this);
	}
	_location_contexts = obj.GetLocationContexts();
	_listen = obj.GetListen();
	_server_name = obj.GetServerNameVector();
	_root = obj.GetRoot();
	_index = obj.GetIndex();
	_client_max_body_size = obj.GetClientMaxBodySize();
	_error_page = obj.GetErrorPage();
    
    // _check_list copy
    _check_list.location_context = obj.GetFlags().location_context;
	_check_list.listen = obj.GetFlags().listen;
	_check_list.server_name = obj.GetFlags().server_name;
	_check_list.root = obj.GetFlags().root;
	_check_list.index = obj.GetFlags().index;
	_check_list.client_max_body_size = obj.GetFlags().client_max_body_size;
	_check_list.error_page = obj.GetFlags().error_page;
	return (*this);
}

// compares found directive with possible directive values and either returns the number in the list
// or throws an error because a bad directive has been found
int			ServerContext::IsDirective(std::string directive){
	const std::string	directives[] = {"location", "listen", "server_name", "root", "index", "client_max_body_size", "error_page"};
	
	int	is_directive = std::find(directives, directives + 7, directive) - directives;
	if (is_directive < 0 || is_directive > 6)
		throw InvalidDirectiveException();
	else
		return (is_directive);
}

// sets the value in the right directive within the server class based off the IsDirective return value
void				ServerContext::SetValue(int directive, std::string value){
	std::string		trimmed_value;

	trimmed_value = TrimValue(value);

	if (directive == 0) {
		_check_list.location_context = true;
		LocationContext	location(trimmed_value);
		for (size_t i = 0 ; i < _location_contexts.size(); ++i){
			if (_location_contexts[i].GetLocationUri().GetUri().compare(location.GetLocationUri().GetUri()) == 0)
			throw DuplicateLocationUriException();
		}
		_location_contexts.push_back(location);
	}
	else {
		switch(directive) {
			case 1: {
				if (_check_list.listen == true)
					throw MultipleListensException();
				_check_list.listen = true;
				Listen	listen_port_ip(trimmed_value);
				_listen.first = listen_port_ip.getIpNumber();
				_listen.second = listen_port_ip.getPortNumber();
				break ;
			}
			case 2: {
				// TODO: still check these
				if (_check_list.server_name == true)
					throw MultipleServerNameException();
				_check_list.server_name = true;
				ServerName	server_name(trimmed_value);
				_server_name = server_name.GetServerNames();
				break ;
			}
			case 3: {
				if (_check_list.root == true)
					throw MultipleRootException();
				_check_list.root = true;
				Root	root_value(trimmed_value);
				_root = trimmed_value; // create a root class and use the GetRoot() function in there to paste root here if valid
				break ;
			}
			case 4:{
				if (_check_list.index == true)
					throw MultipleIndexException();
				_check_list.index = true;
				Index	index_value(trimmed_value);
				_index = index_value.GetIndex(); // create an index class and use the GetIndex() function in there to paste index here if valid
				break ;
			}
			case 5:{
				if (_check_list.client_max_body_size == true)
					throw MultipleClientMaxBodySizeException();
				_check_list.client_max_body_size = true;
				ClientMaxBodySize	cmbs_value(trimmed_value);
				_client_max_body_size = cmbs_value.GetValue();
				break ;
			}
			case 6:{
				_check_list.error_page = true;
				ErrorPage	error_page_value(value);
				_error_page.push_back(error_page_value);
				break ;
			}
		}
	}
	return ;
}

// checks if the necessary blocks have been set and otherwise prints a warning
// if something MUST be set, we should throw an exception
void			ServerContext::CheckListVerification(){
	if (_check_list.location_context == false) {
		//TODO: create a LocationContext constructor that creates the standard / location
		std::cerr << "WARNING! No location context detected. Default have been set." << std::endl;
	}
	if (_check_list.listen == false) {
		_listen.first = 80;
		_listen.second = 0;
		std::cerr << "WARNING! No listen detected. Default have been set." << std::endl;
	}
	if (_check_list.server_name == false) {
		_server_name.push_back("localhost");
		std::cerr << "WARNING! No server_name detected. Default have been set." << std::endl;
	}
	if (_check_list.root == false) {
		_root = "/var/www/html";
		std::cerr << "WARNING! No server root detected. Default have been set." << std::endl;
	}
	if (_check_list.index == false) {
		std::string		str("index.html");
		_index.push_back(str);
		std::cerr << "WARNING! No index detected. Default have been set." << std::endl;
	}
	if (_check_list.client_max_body_size == false) {
		_client_max_body_size = 0;
		std::cerr << "WARNING! No client_max_body_size detected. Default have been set." << std::endl;
	}
	if (_check_list.error_page == false) {
		// hardcoded error pages are used instead?
		std::cerr << "WARNING! No error_page detected. Default have been set." << std::endl;
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
void          ServerContext::FindDirectiveValuePairs(size_t *start_position, std::string config_file) {
	
    int					i = *start_position;
	size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					ret;

	while (config_file[i] != '}') {
		key_start = config_file.find_first_not_of(" \t\n\v\f\r", i);
		if (config_file[key_start] == '}') {
			i = key_start;
			break ;
		}
		key_end = config_file.find_first_of(" \t\n\v\f\r", key_start);
		ret = IsDirective(config_file.substr(key_start, key_end - key_start));
		if (ret == 0) {
			value_end = FindLocationContextEnd(config_file, key_end); //config_file.find_first_of('}', key_end);
			SetValue(ret, config_file.substr(key_end, value_end - key_end + 1));
		}
		else {
			value_end = config_file.find_first_of(';', key_end);
			SetValue(ret, config_file.substr(key_end, value_end - key_end));
		}

		i = value_end + 1;
	}
	*start_position = i;
	CheckListVerification();
}

// check if is set
bool						ServerContext::IsSet(std::string directive) {
	const std::string	directives[] = {"location_context", "listen", "server_name", "root", "index", "client_max_body_size", "error_page"};

	int	is_directive = std::find(directives, directives + 7, directive) - directives;
	if (is_directive < 0 || is_directive > 6)
		throw InvalidDirectiveSetCheckException();
	switch (is_directive) {
		case 0:
			return _check_list.location_context;
		case 1:
			return _check_list.listen;
		case 2:
			return _check_list.server_name;
		case 3:
			return _check_list.root;
		case 4:
			return _check_list.index;
		case 5:
			return _check_list.client_max_body_size;
		case 6:
			return _check_list.error_page;
	}
	throw InvalidDirectiveException();
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

std::string					ServerContext::GetRoot() const {
    return _root;
}

std::vector<std::string>	ServerContext::GetIndex() const {
    return _index;
}

size_t						ServerContext::GetClientMaxBodySize() const {
    return _client_max_body_size;
}

bool						ServerContext::IsErrorPageSet() const {
	return _check_list.error_page;
}

std::vector<ErrorPage>		ServerContext::GetErrorPage() const {
    return _error_page;
}

t_flags_server				ServerContext::GetFlags() const {
	return _check_list;
}