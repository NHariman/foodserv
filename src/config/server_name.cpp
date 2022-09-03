/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_name.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/08 17:01:08 by salbregh      #+#    #+#                 */
/*   Updated: 2022/09/03 15:47:18 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "server_name.hpp"

ServerName::ServerName(std::string server_name): _server_name(server_name) {
	SplitServerNames(_server_name);
}

void ServerName::SplitServerNames(std::string str) {
	std::string	tmp = "";

	
	for (size_t i = 0; i < str.size(); i++) {
		if (!isspace(str[i])) {
			tmp.push_back(str[i]);
			if (i == str.size() - 1) {
				_server_name_vector.push_back(tmp);
				tmp.erase();
			}
		}
		else if (tmp.size() != 0) {
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