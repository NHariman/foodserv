/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nginx_config.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 15:44:12 by salbregh      #+#    #+#                 */
/*   Updated: 2022/08/12 00:04:39 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
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

struct host_target_pair : public std::pair<ServerContext*, LocationContext*> {
	ServerContext *server;
	LocationContext *location;
};

class NginxConfig {
	private:
		std::string					_config_file;
		std::vector<ServerContext>	_servers;
		size_t						_amount_server_contexts;

		bool		IsServerContext(std::string value, size_t *start_pos);
		void		CheckBrackets();
		void		FindServerContexts();
		void		LoadConfigFile(std::ifstream&	configuration_file);

		host_target_pair					GetHostTargetServer(std::string host, std::string target);

	public:
		// coplien form
		NginxConfig();
		NginxConfig(const char*	location);
		NginxConfig & operator=(const NginxConfig& obj);
		~NginxConfig(){};

		// getters
		std::string	GetConfigFile() const;
		size_t		GetServerContextAmount() const;
		std::vector<ServerContext>	GetServers() const;

		size_t		GetMaxBodySize(std::string host, std::string target);
		
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
					return "ERROR! Context found is not a server.";
				}
		};
		
		class InvalidFileLocationException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Cannot open specified file.";
				}
		};

		class CannotFindMaxBodySizeException : public std::exception {
			private:
				std::string _err_msg;
			public:
				CannotFindMaxBodySizeException(std::string host, std::string target) {
					_err_msg = "Cannot find host + target pair: " + host + "/" + target + " client_max_body_size not found.";
				}
				const char *what() const throw() {
					return _err_msg.c_str();
				}
		};
		class HostTargetPairDoesNotExistException : public std::exception {
			private:
				std::string _err_msg;
			public:
				HostTargetPairDoesNotExistException(std::string host, std::string target) {
					_err_msg = "Cannot find host + target pair: " + host + "/" + target + " client_max_body_size not found.";
				}
				const char *what() const throw() {
					return _err_msg.c_str();
				}
		};
};

#endif
