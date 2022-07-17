/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 18:40:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/17 18:27:01 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nginx_config.hpp"
#include <stdexcept>
#include <locale>


// Constructor that takes a file and removes all comments and empty lines
// and saves the string to a variable for passing to the serverblock parser.
// a newline per getline read is added in to avoid cases where for example:
// a key-value pair is on two different lines to avoid accidentally connecting two values with one another.

NginxConfig::NginxConfig() : _amount_server_blocks(0) {};

// uses av[1] in the main and attempts to open the file.
// throws error if fails
// if it loads the _config_file variable
// and closes the file again.
NginxConfig::NginxConfig(const char *location) : _amount_server_blocks(0) {
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
	FindServerBlocks();
	// server blocks listen and server_name part: Sanne
	PrintServerBlocksVectors();
	SplitRequestHost();
}

NginxConfig::NginxConfig(const NginxConfig& obj) {
	_config_file = obj.GetConfigFile();
	_servers = obj.GetServers();
	_amount_server_blocks = obj.GetServerBlockAmount();
}

NginxConfig & NginxConfig::operator=(const NginxConfig& obj) {
	if (this == &obj)
		return (*this);
	_config_file = obj.GetConfigFile();
	_servers = obj.GetServers();
	_amount_server_blocks = obj.GetServerBlockAmount();
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
bool		NginxConfig::IsServerBlock(std::string value, size_t *start_pos) {
	if (value.compare("server") || value.compare("server{")) { 
		if (_config_file[*start_pos + 6] == '{' || std::isspace(_config_file[*start_pos + 6])) {
			*start_pos = *start_pos + 6; // moves to the end of "server"
			while (std::isspace(_config_file[*start_pos]))
				*start_pos = *start_pos + 1;
			if (_config_file[*start_pos] != '{')
				throw BadServerBlockException();
			*start_pos = *start_pos + 1;
			return true;
		}
	}
	throw BadServerBlockException();
	return false;
}

// looks for server{}s
// when it finds one, it increases the _amount_server_block count and adds the server to the vector.
// if no server blocks are found, an error is thrown
void		NginxConfig::FindServerBlocks() {
	size_t		i = 0;
	size_t		key_start = 0;
	size_t		key_end = 0;

	while (_config_file[i]) {
		key_start = _config_file.find_first_not_of(" \t\n\v\f\r", i);
		key_end = _config_file.find_first_of(" \t\n\v\f\r", key_start);
		if (key_start != std::string::npos && key_end != std::string::npos) {
			i = key_start;
			if (IsServerBlock(_config_file.substr(key_start, key_end - key_start), &i)) {
				std::cout << "found a ServerBlock" << std::endl;
				this->_amount_server_blocks++;
				ServerBlock server(&i, _config_file);
				this->_servers.push_back(server);
			}
		}
		i++;
	}
	if (_amount_server_blocks == 0)
		throw NoServerBlocksException();
	return ;
	
}

// SANNE: a function to print what is in the server blocks vector
void	NginxConfig::PrintServerBlocksVectors() {
	for (std::vector<ServerBlock>::iterator it = _servers.begin(); it != _servers.end(); it++) {
		std::cout << "\nIn server block print for loop: " << std::endl;
		std::cout << "PortNumber: " << it->GetPortNumber() << std::endl;
		std::cout << "IPAddress: " << it->GetIPAddress() << std::endl;
		std::vector<std::string> server = it->GetServerNameVector();
		for (std::vector<std::string>::iterator it2 = server.begin(); it2 != server.end(); it2++) {
			std::cout << "In servername vector printing: " << std::endl;
			std::cout << *it2 << std::endl;
		}
	}
}

// for now use example strings that represent the host header:
// Host = uri-host [ ":" port ] ;
// string: www.example.com
// string: example.com:80
// string:
// SANNE: add the functions to select which server block to choose

void	NginxConfig::SplitRequestHost() {
	// std::string	request_host = "example.com:80";
	std::string	request_host = "www.example.com";

	// both request server_name and port_number stay empty
	std::string	request_server_name = "";
	int			request_port_number = -1;
	int			found;

	// if a ':' is found, this means a port number is specified in the request
	// split the server_name and the port_number of the request.
	found = request_host.find(':');
	if (found != std::string::npos) {
		request_port_number = std::stoi(request_host.substr(found + 1, request_host.length()));
		request_server_name = request_host.substr(0, found);
	}
	else
		request_server_name = request_host;

	std::cout << "\nrequest_port_number: " << request_port_number << std::endl;
	std::cout << "request_server_name: " << request_server_name << std::endl;

	// if (request_port_number == -1)
		// go to a function that first adds in compatible serverblocks noted on port number
	// if: its only 1, this is the serverblock
	// else if: multiple, go to server_name chooser
}

void	NginxConfig::ChooseServerBlock() {
	
}

// step1: split the string in server_name and host. request_server_name and request_port
// step2: make a vector of possible server blocks, so where the ports match each other
// 			note: if no port is given, default request_port = 80
// step3: If there is just one match: BINGO this is the server block to use
// step4: If there are multiple matches: start looking at the server_name variable
// step5: First try to find a erver block with a server_name that matches the value request_server_name EXACTLY.
// 			if multiple are found it will use the first one.
// step6:
// step7: If no match is found, Ningx selects the default server block for that IP address and port.
//			The default for IP/port combo will eather be the first block.

// getters
std::string NginxConfig::GetConfigFile() const {
	return this->_config_file;
}

size_t		NginxConfig::GetServerBlockAmount() const {
	return this->_amount_server_blocks;
}

std::vector<ServerBlock>		NginxConfig::GetServers() const {
	return this->_servers;
}

NginxConfig::~NginxConfig() {}