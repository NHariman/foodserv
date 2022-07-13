/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_name.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 17:01:08 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/08 17:02:35 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server_name.hpp"

ServerName::ServerName(std::string server_name): _server_name(server_name) {
	std::cout << "The string that server name gives: " << _server_name << std::endl;
	// if (server_name != "")
	SplitServerNames(_server_name);
}

void ServerName::SplitServerNames(std::string str) {
	// std::cout << "goes in with: " << str <<std::endl;
	std::string	tmp = "";

	// std::cout << "str.size: " << str.size() << std::endl;
	
	for (size_t i = 0; i < str.size(); i++) {
		// std::cout << "I : " << i << ':' << str[i] << std::endl;
		if (!isspace(str[i])) {
			tmp.push_back(str[i]);
			if (i == str.size() - 1) {
				_server_name_vector.push_back(tmp);
				tmp.erase();
			}
		}
		else if (tmp.size() != 0) {
			// std::cout << "value of tmp: " << tmp << std::endl;
			_server_name_vector.push_back(tmp);
			tmp.erase();
		}
	}
}

std::vector<std::string>	ServerName::GetServerNames() {
	return _server_name_vector;
}

void	ServerName::PrintServerNamesVector() {
	for (std::vector<std::string>::iterator it = _server_name_vector.begin(); it != _server_name_vector.end(); it++)
		std::cout << *it << " ";

	std::cout << std::endl;
}