/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listen.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/07 13:10:16 by salbregh      #+#    #+#                 */
/*   Updated: 2022/08/29 11:22:11 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "listen.hpp"

Listen::Listen(std::string listen) { //}: _listen(listen), _port_number(NULL), _ip_number(NULL) {
	std::cout << "String in listen: " << listen << std::endl;
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

// checks for any invalid characters
bool		Listen::CheckCharacters() {
	// std::size_t	pos;
	// pos = _listen.find_first_not_of("0123456789:.");
	// if (pos != std::string::npos)
	// 	return false;
	return true;
}

/*
** Splits the IP and host into 2 different varaibles.
** If : is not in a valid position, false will be returned.
*/
bool		Listen::SplitPortIP() {
	// std::size_t	pos;
	// pos = _listen.find_first_of(":");
	// // add in: if no ':' is found, see if its an IP address or a port
	// if (pos == std::string::npos) {
	// 	if (_listen.find('.') != std::string::npos) {
	// 		if (CheckIpAddress(_listen) == false)
	// 			return false;
	// 	}
	// 	else {
	// 		if (CheckPortNumber(_listen) == false)
	// 			return false;		
	// 	}
	// }
	
	// else if (pos == 0 || (pos == _listen.length() - 1))
	// 	return false;
	// else {
	// 	if (CheckIpAddress(_listen.substr(0, pos)) == false)
	// 		return false;
	// 	if (CheckPortNumber(_listen.substr(pos + 1, _listen.length())) == false)
	// 		return false;
	// }
	return true;
}

bool		Listen::CheckPortNumber(std::string port_number) {			
	// std::size_t	char_check;
	// char_check = port_number.find_first_not_of("0123456789");
	// if (char_check != std::string::npos)
	// 	return false;

	// int check_port;
	
	// // STOI IS C++ 11 CHANGE THIS
	// check_port = stoi(port_number);
	// if (check_port < 0 || check_port > 65535)
	// 	return false;
	(void)port_number;
	return true;
}

bool		Listen::CheckIpAddress(std::string ip_address) {
	// std::size_t	char_check;
	// char_check = ip_address.find_first_not_of("0123456789.");
	// if (char_check != std::string::npos)
	// 	return false;

	// // _ip_number = inet_addr(ip_address.c_str());
	// // if (_ip_number == (in_addr_t)(-1))
	// 	// return false;
	(void)ip_address;
	return true;
}

std::string		Listen::getPortNumber() {
	// return _port_number;
	return "80";
}

std::string		Listen::getIpNumber() {
	// return _ip_number;
	return "[::]"; 
}
