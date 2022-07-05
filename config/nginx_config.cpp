/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 18:40:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/05 20:00:01 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <stdexcept>
#include <locale>

// Constructor that takes a file and removes all comments and empty lines
// and saves the string to a variable for passing to the serverblock parser.
// a newline per getline read is added in to avoid cases where for example:
// a key-value pair is on two different lines to avoid accidentally connecting two values with one another.

NginxConfig::NginxConfig() : _amount_server_blocks(0){};

NginxConfig::NginxConfig(const NginxConfig& obj) {
	this->_config_file = obj.GetConfigFile();
	this->_servers = obj.GetServers();
	this->_amount_server_blocks = obj.GetServerBlockAmount();
}

NginxConfig & NginxConfig::operator=(const NginxConfig& obj) {
	if (this == &obj)
		return (*this);
	this->_config_file = obj.GetConfigFile();
	this->_servers = obj.GetServers();
	this->_amount_server_blocks = obj.GetServerBlockAmount();
	return (*this);
}

void	NginxConfig::LoadConfigFile(std::ifstream& configuration_file) {
	std::string	current_string;
	size_t		found;
	
	while(std::getline(configuration_file, current_string)) {
		if (configuration_file.fail()) {
			throw std::invalid_argument("GetLine failure.");
		}
		if (current_string.find("#") != std::string::npos)
			current_string.erase(current_string.find("#"));
		if (current_string.empty() == false && current_string.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
			this->_config_file.append(current_string + '\n');
	}
}

std::string NginxConfig::GetConfigFile() const {
	return this->_config_file;
}

bool		NginxConfig::IsServerBlock(size_t *start_position) {
	size_t	found = this->_config_file.find("server", *start_position);

	if (found == std::string::npos)
		return false;
	else if (this->_config_file[found + 6] == '{' || std::isspace(this->_config_file[found + 6])) {
		found = found + 6; // moves to the end of "server"
		while (std::isspace(this->_config_file[found]))
			found++;
		if (this->_config_file[found] != '{')
			return false;
		*start_position = found + 1;
		return true;
	}
	return false;
}

size_t		NginxConfig::FindServerBlocks() {
	size_t		found = this->_config_file.find_first_not_of(" \t\n\v\f\r");

	for (size_t i = found; i < this->_config_file.size(); i++) {
		if (IsServerBlock(&i))
		{
			std::cout << "found a ServerBlock" << std::endl;
			this->_amount_server_blocks++;
			ServerBlock server;
			server.FindKeyValuePairs(&i, this->_config_file);
			// this->_configuration.push_back(server);
		}
	}
	return (this->_amount_server_blocks);
}

size_t		NginxConfig::GetServerBlockAmount() const {
	return this->_amount_server_blocks;
}

std::vector<ServerBlock>		NginxConfig::GetServers() const {
	return this->_servers;
}