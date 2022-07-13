/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 18:21:31 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/13 17:16:28 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server_block.hpp"
# include <algorithm>

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


ServerBlock::ServerBlock(size_t *start, std::string config_file) {

    // _check_list copy
    _check_list.location_block = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
	FindKeyValuePairs(start, config_file);
}


ServerBlock::ServerBlock() {
    // _check_list copy
    _check_list.location_block = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
};

ServerBlock::ServerBlock(const ServerBlock& obj) {
	_location_blocks = obj.GetLocationBlocks();
	_listen = obj.GetListen();
	_server_name = obj.GetServerNameVector();
	_root = obj.GetRoot();
	_index = obj.GetIndex();
	_client_max_body_size = obj.GetClientMaxBodySize();
	_error_page = obj.GetErrorPage();

    // _check_list copy
    _check_list.location_block = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
}

ServerBlock & ServerBlock::operator=(const ServerBlock& obj) {
    if (this == &obj)
        return (*this);
	_location_blocks = obj.GetLocationBlocks();
	_listen = obj.GetListen();
	_server_name = obj.GetServerNameVector();
	_root = obj.GetRoot();
	_index = obj.GetIndex();
	_client_max_body_size = obj.GetClientMaxBodySize();
	_error_page = obj.GetErrorPage();
    
    // _check_list copy
    _check_list.location_block = false;
	_check_list.listen = false;
	_check_list.server_name = false;
	_check_list.root = false;
	_check_list.index = false;
	_check_list.client_max_body_size = false;
	_check_list.error_page = false;
	return (*this);
}

// compares found key with possible key values and either returns the number in the list
// or throws an error because a bad key has been found
int			ServerBlock::IsKey(std::string key){
	const std::string	key_name[] = {"location", "listen", "server_name", "root", "index", "client_max_body_size", "error_page"};
	
	std::cout << "key: " << key << std::endl;
	int	is_key = std::find(key_name, key_name + 7, key) - key_name;
	if (is_key < 0 || is_key > 6)
		throw InvalidKeyException();
	else
		return (is_key);
}

// sets the value in the right key within the server class based off the IsKey return value
void				ServerBlock::SetValue(int key, std::string value){
	std::string		trimmed_value;

	trimmed_value = TrimValue(value);
	std::cout << "value: |" << trimmed_value << "|" << std::endl;

	if (key == 0) {
		_check_list.location_block = true;
		LocationBlock	location(trimmed_value);
		for (size_t i = 0 ; i < _location_blocks.size(); ++i){
			if (_location_blocks[i].GetUri().compare(location.GetUri()) == 0)
			throw DuplicateLocationUriException();
		}
		_location_blocks.push_back(location);
	}
	else {
		switch(key) {
			case 1:
			{
				if (_check_list.listen == true)
					throw MultipleListensException();
				_check_list.listen = true;
				Listen	listen_port_ip(trimmed_value);
				_listen.first = listen_port_ip.getIpNumber();
				_listen.second = listen_port_ip.getPortNumber();
				break ;
			}
			case 2:
			{
				// TODO: still check these
				if (_check_list.server_name == true)
					throw MultipleServerNameException();
				_check_list.server_name = true;
				ServerName	server_name(trimmed_value);
				_server_name = server_name.GetServerNames();
				break ;
			}
			case 3:
				if (_check_list.root == true)
					throw MultipleRootException();
				_check_list.root = true;
				_root = value; // create a root class and use the GetRoot() function in there to paste root here if valid
				break ;
			case 4:
				if (_check_list.index == true)
					throw MultipleIndexException();
				_check_list.index = true;
				_index = _index.append(trimmed_value); // create an index class and use the GetIndex() function in there to paste index here if valid
				break ;
			case 5:
				if (_check_list.client_max_body_size == true)
					throw MultipleClientMaxBodySizeException();
				_check_list.client_max_body_size = true;
				_client_max_body_size = std::atoi(value.c_str());
				/// create an CMBS class and use the GetCMBS() function in there to paste CMBS here if valid
				break ;
			case 6:
				_check_list.error_page = true;
				// TODO: create an error_page class for parsing
				// use getter to paste it here if valid
				break ;
		}
	}
	return ;
}

// checks if the necessary blocks have been set and otherwise prints a warning
// if something MUST be set, we should throw an exception
void			ServerBlock::CheckListVerification(){
	if (_check_list.location_block == false) {
		//TODO: create a locationBlock constructor that creates the standard / location
		std::cerr << "WARNING! No location blocks detected. Default have been set." << std::endl;
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
		_index = "index.html";
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

size_t						ServerBlock::FindLocationBlockEnd(std::string config_file, size_t start) {
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
// finds the key and compares it with the possible keys.
// if the key is deemed valid, it checks if a location key has been found
// if so, it grabs the location block to use by looking for the first available }
// otherwise it finds the ';' and sends that substring
// to SetValue, which sets the value in the right key.
// this function keeps checking until the end of the ServerBlock is reached.
void          ServerBlock::FindKeyValuePairs(size_t *start_position, std::string config_file) {
	
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
		ret = IsKey(config_file.substr(key_start, key_end - key_start));
		if (ret == 0) {
			std::cout << "location block found" << std::endl;
			value_end = FindLocationBlockEnd(config_file, key_end); //config_file.find_first_of('}', key_end);
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

//getters
std::vector<LocationBlock>	ServerBlock::GetLocationBlocks() const {
    return this->_location_blocks;
}

std::pair<in_addr_t, int>	ServerBlock::GetListen() const {
    return this->_listen;
}

in_addr_t					ServerBlock::GetIPAddress() const {
	return (this->_listen.first);
}

int							ServerBlock::GetPortNumber() const {
	return (this->_listen.second);
}

std::vector<std::string>	ServerBlock::GetServerNameVector() const {
    return this->_server_name;
}

std::string					ServerBlock::GetRoot() const {
    return this->_root;
}

std::string					ServerBlock::GetIndex() const {
    return this->_index;
}

int							ServerBlock::GetClientMaxBodySize() const {
    return this->_client_max_body_size;
}

bool						ServerBlock::IsErrorPageSet() const {
	return this->_check_list.error_page;
}

std::map<int, std::string>	ServerBlock::GetErrorPage() const {
    return this->_error_page;
}