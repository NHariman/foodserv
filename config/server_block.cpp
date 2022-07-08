/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 18:21:31 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/08 20:35:50 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server_block.hpp"
#include <utility>

// error pages are hardcoded in the real nginx:
// static char ngx_http_error_404_page[] =
// "<html>" CRLF
// "<head><title>404 Not Found</title></head>" CRLF
// "<body>" CRLF
// "<center><h1>404 Not Found</h1></center>" CRLF
//;

// clang++ main.cpp config/server_block.cpp config/location_block.cpp config/nginx_config.cpp && ./a.out 

ServerBlock::ServerBlock() : _client_max_body_size(0){
	// _listen = "80";
	// changed by sanne
	_listen.first = 80;
	_listen.second = 0;
	// _server_name = "localhost";
	_server_name.push_back("localhost"); // feel like we need to take this out
	_root = "/var/www/html";
	_index = "index.html";
	_client_max_body_size = 0;
    //this->_error_page.insert(std::pair<int, std::string>(404, "/404.html")); \
    // if by the end of the FindKeyValuePairs() function no locationblocks or error_pages are found, fill them in?
    // TODO:
    // add defaults for location_blocks

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
	_server_name = obj.GetServerName();
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
	_server_name = obj.GetServerName();
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

// trims whitespaces from the front and back
// could probably be made into something general. but for now this'll do.
// std::string	ServerBlock::TrimValue(std::string value){
// 	size_t	start = 0;
// 	size_t	end = 0;

// 	start = value.find_first_not_of(" \t\n\v\f\r");
// 	end = value.find_last_not_of(" \t\n\v\f\r");
// 	return (value.substr(start, end - start + 1));
// }

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
int				ServerBlock::SetValue(int key, std::string value){
	std::string		trimmed_value;

	trimmed_value = TrimValue(value);
	std::cout << "value: |" << trimmed_value << "|" << std::endl;

	if (key == 0) {
		_check_list.location_block = true;
		LocationBlock	location(trimmed_value);
		_location_blocks.push_back(location);
	}
	else {
		switch(key) {
			case 1:
			{
				if (_check_list.listen == true)
					throw MultipleListensException();
				_check_list.listen = true;
				// SANNE: TRIMMED_VALUE CONTAINS THE STRING CONTAINING THE VALUE FOR LISTEN
				// YOU CAN PUT YOU CAN INITIALISE YOUR LISTEN CLASS HERE AND USE THE TRIMMED_VALUE
				// VARIABLE AS STRING
				//_listen = value;
				// changed by sanne
				Listen	listen_port_ip(value);
				_listen.first = listen_port_ip.getIpNumber();
				_listen.second = listen_port_ip.getIpNumber();
				break ;
			}
			case 2:
			{
				_check_list.server_name = true;
				// SANNE: TRIMMED_VALUE CONTAINS THE STRING CONTAINING THE VALUE FOR SERVER_NAME
				// YOU CAN PUT YOU CAN INITIALISE YOUR SERVER_NAME CLASS HERE AND USE THE TRIMMED_VALUE
				// VARIABLE AS STRING
				// changed by sanne
				ServerName	server_name(value);
				_server_name = server_name.GetServerNames();
				//_server_name = value;
				break ;
			}
			case 3:
				_check_list.root = true;
				_root = value;
				break ;
			case 4:
				_check_list.index = true;
				_index = value;
				break ;
			case 5:
				_check_list.client_max_body_size = true;
				_client_max_body_size = std::atoi(value.c_str());
				// TODO: INPUT CHECK. CHECK IF VALUE IS A NUMBER
				break ;
			case 6:
				_check_list.error_page = true;
				// TODO: DEPENDENT ON LOCATION
				break ;
		}
	}
	return (0);
}

// checks if the necessary blocks have been set and otherwise prints a warning
// if something MUST be set, we should throw an exception
void			ServerBlock::CheckListVerification(){
	if (_check_list.location_block == false)
		std::cerr << "WARNING! No location blocks detected. Default have been set." << std::endl;
	if (_check_list.listen == false)
		std::cerr << "WARNING! No listen detected. Default have been set." << std::endl;
	if (_check_list.server_name == false)
		std::cerr << "WARNING! No server_name detected. Default have been set." << std::endl;
	if (_check_list.root == false)
		std::cerr << "WARNING! No server root detected. Default have been set." << std::endl;
	if (_check_list.index == false)
		std::cerr << "WARNING! No index detected. Default have been set." << std::endl;
	if (_check_list.client_max_body_size == false)
		std::cerr << "WARNING! No client_max_body_size detected. Default have been set." << std::endl;
	if (_check_list.error_page == false)
		std::cerr << "WARNING! No error_page detected. Default have been set." << std::endl;
}

// starts after the { of the server{ 
// finds the key and compares it with the possible keys.
// if the key is deemed valid, it checks if a location key has been found
// if so, it grabs the location block to use by looking for the first available }
// otherwise it finds the ';' and sends that substring
// to SetValue, which sets the value in the right key.
// this function keeps checking until the end of the ServerBlock is reached.
size_t          ServerBlock::FindKeyValuePairs(size_t *start_position, std::string config_file) {
	
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
			value_end = config_file.find_first_of('}', key_end);
		}
		else
			value_end = config_file.find_first_of(';', key_end);
		SetValue(ret, config_file.substr(key_end, value_end - key_end));
		i = value_end + 1;
	}
	*start_position = i;
	CheckListVerification();
    return (*start_position);
}

//getters
std::vector<LocationBlock>	ServerBlock::GetLocationBlocks() const {
    return this->_location_blocks;
}

std::pair<in_addr_t, int>	ServerBlock::GetListen() const {
    return this->_listen;
}

std::vector<std::string>	ServerBlock::GetServerName() const {
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

std::map<int, std::string>	ServerBlock::GetErrorPage() const {
    return this->_error_page;
}