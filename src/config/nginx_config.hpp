/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/08/01 16:35:53 by salbregh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "server_context.hpp"
#include "config_utils.hpp"

// Coplien form:

// class A final
// {
//    public:
//       A ();
//       A (const A &a);
//       ~A ();
//       A & operator = (const A &a);
// };

// TODO:
// create basic error checking, open brackets etc.

class NginxConfig {
	private:
		std::string					_config_file;
		std::vector<ServerContext>	_servers;
		size_t						_amount_server_contexts;

		NginxConfig();
		bool		IsServerContext(std::string value, size_t *start_pos);
		void		CheckBrackets();
		void		FindServerContexts();
		void		LoadConfigFile(std::ifstream&	configuration_file);

	public:
		// coplien form
		NginxConfig(const char*	location);
		NginxConfig(const NginxConfig& obj);
		~NginxConfig();
		NginxConfig & operator=(const NginxConfig& obj);

		// getters
		std::string	GetConfigFile() const;
		size_t		GetServerContextAmount() const;
		std::vector<ServerContext>	GetServers() const;
		
		//exceptions
		class GetLineFailureException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! std::getline failure.";
				}
		};
		
		class OpenBracketsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Open brackets detected.";
				}
		};
		
		class NoServerContextsException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! No servers detected.";
				}
		};

		class BadServerContextException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Bad server keyword detected.";
				}
		};
		
		class InvalidFileLocationException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Cannot open specified file.";
				}
		};
};

#endif
