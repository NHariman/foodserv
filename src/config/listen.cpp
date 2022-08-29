/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listen.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 13:10:16 by salbregh      #+#    #+#                 */
/*   Updated: 2022/08/29 16:11:10 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "listen.hpp"

// step 1: split IP and Port from eachother.
// step 2: If nothing to split, check if IP or port is found; set missing values to their defaults
// step 3: If port, check port
// step 4: If ip, check IP

// DEFAULT PORT = 80
// DEFAULT IP is in any address 0.0.0.0 for ipv4 and [::0] for IPv6 

Listen::Listen(std::string listen) : _listen(listen) {
	std::cout << std::endl << "String in listen: " << _listen << std::endl;
	if (_listen.empty()) {
		_port_number = "80";
		_ip_number = "0";
		std::cout << "defaults set" << std::endl;
		return ;
	}

	SplitPortIP();
	// std::cout << "gets here" << std::endl;
	// if (CheckCharacters() == false || SplitPortIP() == false) {
		// std::cout << "webserv: invalid port/ip in \"" << _listen << "\" of the \"listen\" directive." << std::endl;
	// 	// _ip_number = -1; // dit is 4294967295
	// 	// _port_number = -1;
	// 	// implement what happens when this is invalid
	// 	return ;
	// }
	// // if (_ip_number == in_addr_t(std::string::npos))
	// // 	_ip_number = "0.0.0.0";
}

/*
** Splits the IP and host into 2 different varaibles.
** If : is not in a valid position, false will be returned.
*/
void		Listen::SplitPortIP() {
	std::size_t	pos;
	pos = _listen.find_last_of(":");
	// only IP or port is given , figure out which one
	if (pos == std::string::npos || (_listen.front() == '[' && _listen.back() == ']')) {
		std::cout << "only one value is given" << std::endl;
		if (_listen.find('.') != std::string::npos || _listen.find(':') != std::string::npos
			|| _listen.find("localhost") != std::string::npos || _listen.find("*") != std::string::npos) {
			std::cout << "must be an IP" << std::endl;
			CheckIpAddress(_listen);
		}
		else {
			std::cout << "Must be a port" << std::endl;
			CheckPortNumber(_listen);
		}
	}
	// both IP and port are given
	else {
		CheckIpAddress(_listen.substr(0, pos));
		CheckPortNumber(_listen.substr(pos + 1, _listen.size()));
	}
}

void		Listen::CheckPortNumber(std::string port_number) {			
	(void)port_number;
	std::cout << "in check port number with: >" << port_number << "<" << std::endl;
	if (port_number.find_first_not_of("0123456789") != std::string::npos)
		throw InvalidPortException();
}

void		Listen::CheckIpAddress(std::string ip_address) {
	(void)ip_address;
	std::cout << "in check IP number with >" << ip_address << "<" << std::endl;
	if (ip_address == "localhost")
		_ip_number = "127.0.0.1";
	else if (ip_address == "0")
		_ip_number = "0";
}

std::string		Listen::getPortNumber() {
	return _port_number;
	// return "80";
}

std::string		Listen::getIpNumber() {
	return _ip_number;
	// return "[::]";
}
