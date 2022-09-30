#include "nginx_config.hpp"
#include "directive_validation/directive_validation.hpp"
#include <stdexcept>
#include <locale>

#define DEBUG 0

// Constructor that takes a file and removes all comments and empty lines
// and saves the string to a variable for passing to the ServerContext parser.
// a newline per getline read is added in to avoid cases where for example:
// a key-value pair is on two different lines to avoid accidentally connecting two values with one another.

NginxConfig::NginxConfig() : _amount_server_contexts(0) {
	std::ifstream	config_file_fd;
	if (DEBUG) std::cout << "default constructor" << std::endl;
	config_file_fd.open("config_files/default.conf");
	if (config_file_fd.is_open()) 
		LoadConfigFile(config_file_fd);
	else
		throw InvalidFileLocationException();
	config_file_fd.close();
	FindServerContexts();
};

// uses av[1] in the main and attempts to open the file.
// throws error if fails
// if it loads the _config_file variable
// and closes the file again.
NginxConfig::NginxConfig(const char *location) : _amount_server_contexts(0) {
	std::ifstream	config_file_fd;
	
	if (!location) {
		location = "config_files/default.conf";
		std::cerr << ">> WARNING! No config file given, config_files/default.conf used." << std::endl;
	}
	config_file_fd.open(location);
	if (config_file_fd.is_open()) 
		LoadConfigFile(config_file_fd);
	else
		throw InvalidFileLocationException();
	config_file_fd.close();
	FindServerContexts();
}

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

#undef DEBUG
