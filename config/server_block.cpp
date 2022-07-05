/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/05 18:21:31 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/05 20:10:23 by nhariman      ########   odam.nl         */
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
;

ServerBlock::ServerBlock() : _client_max_body_size(0){
	this->_listen = "80";
	this->_server_name = "localhost";
	this->_root = "/var/www/html";
	this->_index = "index.html";
	this->_client_max_body_size = 0;
    //this->_error_page.insert(std::pair<int, std::string>(404, "/404.html")); \
    // if by the end of the FindKeyValuePairs() function no locationblocks or error_pages are found, fill them in?
    // TODO:
    // add defaults for location_blocks

    // _check_list copy
    this->_check_list.location_block = false;
	this->_check_list.listen = false;
	this->_check_list.server_name = false;
	this->_check_list.root = false;
	this->_check_list.index = false;
	this->_check_list.client_max_body_size = false;
	this->_check_list.error_page = false;
};

ServerBlock::ServerBlock(const ServerBlock& obj) {
	this->_location_blocks = obj.GetLocationBlocks();
	this->_listen = obj.GetListen();
	this->_server_name = obj.GetServerName();
	this->_root = obj.GetRoot();
	this->_index = obj.GetIndex();
	this->_client_max_body_size = obj.GetClientMaxBodySize();
	this->_error_page = obj.GetErrorPage();

    // _check_list copy
    this->_check_list.location_block = false;
	this->_check_list.listen = false;
	this->_check_list.server_name = false;
	this->_check_list.root = false;
	this->_check_list.index = false;
	this->_check_list.client_max_body_size = false;
	this->_check_list.error_page = false;
}

ServerBlock & ServerBlock::operator=(const ServerBlock& obj) {
    if (this == &obj)
        return (*this);
	this->_location_blocks = obj.GetLocationBlocks();
	this->_listen = obj.GetListen();
	this->_server_name = obj.GetServerName();
	this->_root = obj.GetRoot();
	this->_index = obj.GetIndex();
	this->_client_max_body_size = obj.GetClientMaxBodySize();
	this->_error_page = obj.GetErrorPage();
    
    // _check_list copy
    this->_check_list.location_block = false;
	this->_check_list.listen = false;
	this->_check_list.server_name = false;
	this->_check_list.root = false;
	this->_check_list.index = false;
	this->_check_list.client_max_body_size = false;
	this->_check_list.error_page = false;
	return (*this);
}

size_t          ServerBlock::FindKeyValuePairs(size_t *start_position, std::string config_file)
{
    std::cout << "yea" << std::endl;
    std::cout << config_file.substr(*start_position) << std::endl;
    return (*start_position);
}

//getters
std::vector<LocationBlock>	ServerBlock::GetLocationBlocks() const {
    return this->_location_blocks;
}

std::string					ServerBlock::GetListen() const {
    return this->_listen;
}

std::string					ServerBlock::GetServerName() const {
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