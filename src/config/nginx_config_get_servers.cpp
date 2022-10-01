#include "nginx_config.hpp"

// skips to the end of the word server and its subsequent { bracket
void        NginxConfig::MoveIntoServerBlock(size_t *start_pos) {
    *start_pos = *start_pos + 6; // moves to the end of "server"
	while (std::isspace(_config_file[*start_pos]))
		*start_pos = *start_pos + 1;
	if (_config_file[*start_pos] != '{')
		throw BadServerContextException();
	*start_pos = *start_pos + 1;
}

// checks if the server block is correctly written and then moves to the end of the word
bool		NginxConfig::IsServerContext(std::string value, size_t *start_pos) {
	if (value.compare("server") || value.compare("server{")) { 
		if (_config_file[*start_pos + 6] == '{' || std::isspace(_config_file[*start_pos + 6])) {
            MoveIntoServerBlock(start_pos);
			return true;
		}
	}
	throw BadServerContextException();
	return false;
}

void        NginxConfig::SetServerContext(size_t *i) {
    _amount_server_contexts++;
	ServerContext server(i, _config_file, _amount_server_contexts);
	_servers.push_back(server);
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
                SetServerContext(&i);
			}
		}
		if (i != std::string::npos)
			i++;
	}
	if (_amount_server_contexts == 0)
		throw NoServerContextsException();
	return ;
}