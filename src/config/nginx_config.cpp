/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 18:40:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/21 13:12:55 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <stdexcept>
#include <locale>


// Constructor that takes a file and removes all comments and empty lines
// and saves the string to a variable for passing to the ServerContext parser.
// a newline per getline read is added in to avoid cases where for example:
// a key-value pair is on two different lines to avoid accidentally connecting two values with one another.

NginxConfig::NginxConfig() : _amount_server_contexts(0) {};

// uses av[1] in the main and attempts to open the file.
// throws error if fails
// if it loads the _config_file variable
// and closes the file again.
NginxConfig::NginxConfig(const char *location) : _amount_server_contexts(0) {
	std::ifstream	config_file_fd;

	if (!location) {
		location = "config_files/default.conf";
		std::cerr << ">> WARNING! No config file given, config/default.conf used." << std::endl;
	}
	config_file_fd.open(location);
	if (config_file_fd.is_open()) 
		LoadConfigFile(config_file_fd);
	else
		throw InvalidFileLocationException();
	config_file_fd.close();
	FindServerContexts();
}

NginxConfig::NginxConfig(const NginxConfig& obj) {
	_config_file = obj.GetConfigFile();
	_servers = obj.GetServers();
	_amount_server_blocks = obj.GetServerContextAmount();
}

NginxConfig & NginxConfig::operator=(const NginxConfig& obj) {
	if (this == &obj)
		return (*this);
	_config_file = obj.GetConfigFile();
	_servers = obj.GetServers();
	_amount_server_contexts = obj.GetServerContextAmount();
	return (*this);
}

// checks if there are no open brackets
void	NginxConfig::CheckBrackets() {
	int open_brackets = 0;
	int closed_brackets = 0;
	int	i = 0;

	// while (_config_file[i] != std::string::npos) {
	while (_config_file[i]) {
		if (_config_file[i] == '{')
			open_brackets++;
		else if (_config_file[i] == '}')
			closed_brackets++;
		i++;
	}
	if (open_brackets == closed_brackets)
		return ;
	else
		throw OpenBracketsException();
}

// gets the content from the file and removes all comments
void	NginxConfig::LoadConfigFile(std::ifstream& configuration_file) {
	std::string	current_string;
	
	while(std::getline(configuration_file, current_string)) {
		if (configuration_file.fail())
			throw GetLineFailureException();
		if (current_string.find("#") != std::string::npos)
			current_string.erase(current_string.find("#"));
		if (current_string.empty() == false && current_string.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
			_config_file.append(current_string + '\n');
	}
	CheckBrackets();
}

// checks if the server block is correctly written
bool		NginxConfig::IsServerContext(std::string value, size_t *start_pos) {
	if (value.compare("server") || value.compare("server{")) { 
		if (_config_file[*start_pos + 6] == '{' || std::isspace(_config_file[*start_pos + 6])) {
			*start_pos = *start_pos + 6; // moves to the end of "server"
			while (std::isspace(_config_file[*start_pos]))
				*start_pos = *start_pos + 1;
			if (_config_file[*start_pos] != '{')
				throw BadServerContextException();
			*start_pos = *start_pos + 1;
			return true;
		}
	}
	throw BadServerContextException();
	return false;
}

// looks for server{}s
// when it finds one, it increases the _amount_server_block count and adds the server to the vector.
// if no server blocks are found, an error is thrown
void		NginxConfig::FindServerContexts() {
	size_t		i = 0;
	size_t		key_start = 0;
	size_t		key_end = 0;

	// while (_config_file[i] != std::string::npos) {
	while (_config_file[i]) {
		key_start = _config_file.find_first_not_of(" \t\n\v\f\r", i);
		key_end = _config_file.find_first_of(" \t\n\v\f\r", key_start);
		if (key_start != std::string::npos && key_end != std::string::npos) {
			i = key_start;
			if (IsServerContext(_config_file.substr(key_start, key_end - key_start), &i)) {
				std::cout << "found a ServerContext" << std::endl;
				this->_amount_server_blocks++;
				ServerContext server(&i, _config_file);
				this->_servers.push_back(server);
			}
		}
		i++;
	}
	if (_amount_server_contexts == 0)
		throw NoServerContextsException();
	return ;
	
}

// SANNE: a function to print what is in the server blocks vector
void	NginxConfig::PrintServerContextsVectors() {
	for (std::vector<ServerContext>::iterator it = _servers.begin(); it != _servers.end(); it++) {
		std::cout << "\nIn server block print for loop: " << std::endl;
		std::cout << "PortNumber: " << it->GetIPAddress() << std::endl;
		std::cout << "IPAddress: " << it->GetPortNumber() << std::endl;
		// DANGLING POINTER ERROR: 
		for (std::vector<std::string>::iterator it2 = it->GetServerNameVector().begin(); it2 != it->GetServerNameVector().end(); it2++) {
			std::cout << "In servername vector printing: " << std::endl;
			std::cout << *it2 << std::endl;
		}
	}
}

// SANNE: add the functions to select which server block to choose


// getters
std::string NginxConfig::GetConfigFile() const {
	return this->_config_file;
}

size_t		NginxConfig::GetServerContextAmount() const {
	return this->_amount_server_contexts;
}

std::vector<ServerContext>		NginxConfig::GetServers() const {
	return this->_servers;
}

NginxConfig::~NginxConfig() {}