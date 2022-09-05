
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

// checks if there are no open brackets
void	NginxConfig::CheckBrackets() {
	int open_brackets = 0;
	int closed_brackets = 0;
	int	i = 0;

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

	while (_config_file[i]) {
		key_start = _config_file.find_first_not_of(" \t\n\v\f\r", i);
		if (key_start == std::string::npos)
			break ;
		key_end = _config_file.find_first_of(" \t\n\v\f\r", key_start);
		if (key_end != std::string::npos) {
			i = key_start;
			if (IsServerContext(_config_file.substr(key_start, key_end - key_start), &i)) {
				this->_amount_server_contexts++;
				ServerContext server(&i, _config_file, _amount_server_contexts);
				this->_servers.push_back(server);
			}
		}
		if (i != std::string::npos)
			i++;
	}
	if (_amount_server_contexts == 0)
		throw NoServerContextsException();
	return ;
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

bool								NginxConfig::IsSetInTarget(std::string host, std::string target, std::string directive) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	return host_target_pair.location.IsSet(directive);
}

bool								NginxConfig::IsSetInHost(std::string host, std::string directive) const {
	ServerContext	 host_serv(GetHostServer(host));
	return host_serv.IsSet(directive);
}

std::string							NginxConfig::GetRoot(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("root"))
		return host_target_pair.location.GetRoot();
	return host_target_pair.server.GetRoot();
}

std::vector<std::string>			NginxConfig::GetIndex(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("index"))
		return host_target_pair.location.GetIndex();
	return host_target_pair.server.GetIndex();
}

size_t								NginxConfig::GetMaxBodySize(std::string host, std::string target) const {

	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("client_max_body_size"))
		return host_target_pair.location.GetClientMaxBodySize();
	return host_target_pair.server.GetClientMaxBodySize();
}

std::vector<ErrorPage>				NginxConfig::GetErrorPage(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("error_page"))
		return host_target_pair.location.GetErrorPage();
	else if (host_target_pair.server.IsSet("error_page"))
		return host_target_pair.server.GetErrorPage();
	throw ConfigValues::DirectiveNotSetException("error_page", host, target);
}

bool								NginxConfig::GetAutoindex(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("autoindex"))
		return host_target_pair.location.GetAutoindex();
	return host_target_pair.server.GetAutoindex();
}

ReturnDir							NginxConfig::GetReturn(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("return"))
		return host_target_pair.location.GetReturn();
	else if (host_target_pair.server.IsSet("return"))
		return host_target_pair.server.GetReturn();
	throw ConfigValues::DirectiveNotSetException("return", host, target);
}

bool							NginxConfig::IsAllowedMethod(std::string host, std::string target, std::string method) const {
	host_target_pair	host_target_pair = GetHostTargetServer(host, target);

	switch (IsValidHTTPMethod(method)) {
		case GET:
			return host_target_pair.location.GetAllowedMethods().GetGET();
		case POST:
			return host_target_pair.location.GetAllowedMethods().GetPOST();
		case DELETE:
			return host_target_pair.location.GetAllowedMethods().GetDELETE();
	}
	return false;
}

CGIPass					NginxConfig::GetCGIPass(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("cgi_pass"))
		return host_target_pair.location.GetCGIPass();
	throw ConfigValues::DirectiveNotSetException("cgi_pass", host, target);
}

#undef DEBUG
