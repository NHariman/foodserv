/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 18:40:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/09 00:58:13 by nhariman      ########   odam.nl         */
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

// uses av[1] in the main and attempts to open the file.
// throws error if fails
// if it loads the _config_file variable
// and closes the file again.
NginxConfig::NginxConfig(const char*	location) : _amount_server_blocks(0){
	std::ifstream	config_file_fd;

	if (!location) {
		location = "config/default.conf";
		std::cerr << ">> WARNING! No config file given, config/default.conf used." << std::endl;
	}
	config_file_fd.open(location);
	if (config_file_fd.is_open()) 
		LoadConfigFile(config_file_fd);
	else 
		throw InvalidFileLocationException();
	config_file_fd.close();
	FindServerBlocks();
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
void	NginxConfig::CheckBrackets(){
	int open_brackets = 0;
	int closed_brackets = 0;
	int	i = 0;

	while(_config_file[i] != std::string::npos)
	{
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
	size_t		found;
	
	while(std::getline(configuration_file, current_string)) {
		if (configuration_file.fail()) {
			throw GetLineFailureException();
		}
		if (current_string.find("#") != std::string::npos)
			current_string.erase(current_string.find("#"));
		if (current_string.empty() == false && current_string.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
			_config_file.append(current_string + '\n');
	}
	CheckBrackets();
}

// checks if the server block is correctly written
bool		NginxConfig::IsServerBlock(size_t *start_position) {
	size_t	end_position = _config_file.find_first_of(" \t\n\v\f\r", *start_position);
	// std::string	key = _config_file.substr(*start_position, end_position - *start_position);
	size_t	found = _config_file.find("server", *start_position);

	if (found == std::string::npos)
		return false;
	else if (_config_file[found + 6] == '{' || std::isspace(_config_file[found + 6])) {
		found = found + 6; // moves to the end of "server"
		while (std::isspace(_config_file[found]))
			found++;
		if (_config_file[found] != '{')
			throw BadServerBlockException();
		*start_position = found + 1;
		return true;
	}
	// else if (key.compare("server") != 0)
	// 	throw BadKeywordException();
	return false;
}

// looks for server{}s
// when it finds one, it increases the _amount_server_block count and adds the server to the vector.
// if no server blocks are found, an error is thrown
void		NginxConfig::FindServerBlocks() {
	size_t		i = _config_file.find_first_not_of(" \t\n\v\f\r", i);

	while(_config_file[i] != std::string::npos) {
		if (IsServerBlock(&i))
		{
			std::cout << "found a ServerBlock" << std::endl;
			this->_amount_server_blocks++;
			ServerBlock server(&i, _config_file);
			this->_servers.push_back(server);
			//std::cout << _config_file.substr(i);
		}
		i++;
	}
	if (_amount_server_blocks == 0)
		throw NoServerBlocksException();
	return ;
}


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