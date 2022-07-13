/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_block.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:36 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/13 16:23:45 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "location_block.hpp"

std::string	TrimValue(std::string value){
	size_t	start = 0;
	size_t	end = 0;

	start = value.find_first_not_of(" \t\n\v\f\r");
	end = value.find_last_not_of(" \t\n\v\f\r");
	return (value.substr(start, end - start + 1));
}

LocationBlock::LocationBlock(std::string data) {
    std::cerr << "In LocationBlock now" << std::endl;
    _check_list.uri = false;
    _check_list.autoindex = false;
    _check_list.root = false;
    _check_list.index = false;
    _check_list.client_max_body_size = false;
	_check_list.error_page = false;
    _check_list.proxy_pass = false;
	_check_list.limit_except = false;
    GetKeyValuePairs(data);
}

LocationBlock& LocationBlock::operator= (const LocationBlock& location_block) {
    if (this == &location_block)
        return (*this);
    _uri = location_block.GetUri();
    _autoindex = location_block.GetAutoindex();
    _root = location_block.GetRoot();
    _index = location_block.GetIndex();
    _client_max_body_size = location_block.GetClientMaxBodySize();
	_error_page = location_block.GetErrorPage();
    _proxy_pass = location_block.GetProxyPass();
	_limit_except = location_block.GetLimitExcept();
    return (*this);
}
LocationBlock::LocationBlock(const LocationBlock& location_block) {
    _uri = location_block.GetUri();
    _autoindex = location_block.GetAutoindex();
    _root = location_block.GetRoot();
    _index = location_block.GetIndex();
    _client_max_body_size = location_block.GetClientMaxBodySize();
	_error_page = location_block.GetErrorPage();
    _proxy_pass = location_block.GetProxyPass();
	_limit_except = location_block.GetLimitExcept();
}

int			            LocationBlock::IsKey(std::string key) {
	const std::string	key_name[] = {"autoindex", "root", "index", "client_max_body_size", "error_page", "proxy_pass", "limit_except"};
	
	std::cout << "key: " << key << std::endl;
    if (_check_list.uri == false)
        return 7;
	int	is_key = std::find(key_name, key_name + 7, key) - key_name;
	if (is_key < 0 || is_key > 6)
		throw InvalidKeyException();
	else
		return (is_key);
}

void				LocationBlock::SetValue(int key, std::string value) {
	std::string		trimmed_value;

	trimmed_value = TrimValue(value);
	std::cout << "value: |" << trimmed_value << "|" << std::endl;

	if (key == 7) {
		_check_list.uri = true;
		_uri = trimmed_value;
        //do thing
	}
	else {
		switch(key) {
			case 0: {
				_check_list.autoindex = true;
				break ;
			}
			case 1:
				_check_list.root = true;
				_root = value;
				break ;
			case 2:
				_check_list.index = true;
				_index = value;
				break ;
			case 3:
				_check_list.client_max_body_size = true;
				_client_max_body_size = std::atoi(value.c_str());
				// TODO: INPUT CHECK. CHECK IF VALUE IS A NUMBER
				break ;
            case 4:
				_check_list.error_page = true;
				// TODO: INPUT CHECK. CHECK IF VALUE IS A NUMBER
				break ;
            case 5:
				_check_list.proxy_pass = true;
				// TODO: INPUT CHECK. CHECK IF VALUE IS A NUMBER
				break ;
            case 6:
				_check_list.limit_except = true;
				// TODO: INPUT CHECK. CHECK IF VALUE IS A NUMBER
				break ;
		}
	}
}

void			LocationBlock::CheckListVerification(){
	if (_check_list.uri == false)
		std::cerr << "WARNING! No uri in locationblock detected. Default have been set." << std::endl;
    if (_check_list.autoindex == false)
		std::cerr << "WARNING! No autoindex in locationblock detected. Default have been set." << std::endl;
    if (_check_list.root == false)
		std::cerr << "WARNING! No location root detected. Default have been set." << std::endl;
	if (_check_list.index == false)
		std::cerr << "WARNING! No location index detected. Default have been set." << std::endl;
	if (_check_list.client_max_body_size == false)
		std::cerr << "WARNING! No client_max_body_size in locationblock detected. Default have been set." << std::endl;
	if (_check_list.proxy_pass == false)
		std::cerr << "WARNING! No proxy_pass in locationblock detected. Default have been set." << std::endl;
}

void                        LocationBlock::GetKeyValuePairs(std::string data) {
    size_t				key_start = 0;
	size_t				key_end = 0;
	size_t				value_end = 0;
	int					ret;
    int                 i = 0;
    
    while (data[i] != '}') {
		key_start = data.find_first_not_of(" \t\n\v\f\r", i);
		if (data[key_start] == '}') {
			break ;
		}
		key_end = data.find_first_of(" \t\n\v\f\r", key_start);
		ret = IsKey(data.substr(key_start, key_end - key_start));
		if (ret == 7) {
			std::cout << "uri block found" << std::endl;
            SetValue(ret, data.substr(key_start, key_end - key_start));
			value_end = data.find_first_of('{', key_end);
		}
		else if (ret == 6) {
			value_end = data.find_first_of('}', key_end);
			SetValue(ret, data.substr(key_end, value_end - key_end + 1));
		}
		else {
            value_end = data.find_first_of(';', key_end);
		    SetValue(ret, data.substr(key_end, value_end - key_end));
        }
		i = value_end + 1;
	}
	CheckListVerification();
}

// getters
std::string					LocationBlock::GetUri() const {
    return this->_uri;
}

bool						LocationBlock::GetAutoindex() const {
    return this->_autoindex;
}

std::string					LocationBlock::GetRoot() const {
    return this->_root;
}

std::string					LocationBlock::GetIndex() const {
    return this->_index;
}

int							LocationBlock::GetClientMaxBodySize() const {
    return this->_client_max_body_size;
}

std::string	                LocationBlock::GetErrorPage() const {
    return this->_error_page;
}

std::string	                LocationBlock::GetProxyPass() const {
    return this->_proxy_pass;
}

std::string	                LocationBlock::GetLimitExcept() const {
    return this->_limit_except;
}