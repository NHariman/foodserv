/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   listen.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 16:13:56 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/30 16:18:24 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <iostream>
#include <string>
#include <arpa/inet.h>

/*
**	NOTES:

**	The listen directive 

**	- port cant be negative and not bigger than 65535

**	FUNCTIONS:
**	- htonl: 
**	- htons: 

	example from server part: 
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(8080);

*/

class Listen {
	private:
		std::string	_listen;
		int			_port_number; // htons?
		in_addr_t	_ip_number; // change to int? it htons htlons whatever
		
	private:
		Listen();
		Listen(const Listen& x);
		Listen& operator=(const Listen& rhs);

	public:
		Listen(std::string listen);
		
		bool		CheckCharacters();
		bool		SplitPortIP();
		bool		CheckPortNumber(std::string port_number);
		bool		CheckIpAddress(std::string ip_address);
		int			getPortNumber();
		in_addr_t	getIpNumber();
};

#endif
