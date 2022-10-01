#include "nginx_config.hpp"

// checks if there are no open brackets in the file
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