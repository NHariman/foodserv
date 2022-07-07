/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_block.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:36 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/07 21:27:58 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "location_block.hpp"

LocationBlock::LocationBlock(std::string data) {

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
    return (*this);
}
LocationBlock::LocationBlock(const LocationBlock& location_block) {
    _uri = location_block.GetUri();
    _autoindex = location_block.GetAutoindex();
    _root = location_block.GetRoot();
    _index = location_block.GetIndex();
    _client_max_body_size = location_block.GetClientMaxBodySize();
    _error_page = location_block.GetErrorPage();
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

std::map<int, std::string>	LocationBlock::GetErrorPage() const {
    return this->_error_page;
}