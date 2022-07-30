/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_name.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: salbregh <salbregh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/04 16:13:59 by salbregh      #+#    #+#                 */
/*   Updated: 2022/07/30 16:20:10 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_NAME_HPP
# define SERVER_NAME_HPP

#include <iostream>
#include <string>
#include <vector>

class ServerName {
	private:
		std::string					_server_name;
		std::vector<std::string>	_server_name_vector;

	private:
		ServerName();
		ServerName(const ServerName& x);
		ServerName&	operator=(const ServerName& rhs);
		
	public:
		ServerName(std::string server_name);
		void 						SplitServerNames(std::string str);
		std::vector<std::string>	GetServerNames();
		void						PrintServerNamesVector(); // for error checking
		
		
};

#endif