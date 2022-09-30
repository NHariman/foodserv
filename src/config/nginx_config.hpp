#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "server_context.hpp"

class NginxConfig {
	private:
		std::string					_config_file;
		std::vector<ServerContext>	_servers;
		size_t						_amount_server_contexts;

		bool		IsServerContext(std::string value, size_t *start_pos);
		void		CheckBrackets();
		void		FindServerContexts();
		void		LoadConfigFile(std::ifstream&	configuration_file);
		void		SetServerContext(size_t *i);
		void        MoveIntoServerBlock(size_t *start_pos);

	public:
		// coplien form
		NginxConfig();
		NginxConfig(const char*	location);
		NginxConfig & operator=(const NginxConfig& obj);
		~NginxConfig(){};

		// getters
		std::string					GetConfigFile() const;
		size_t						GetServerContextAmount() const;
		std::vector<ServerContext>	GetServers() const;

		size_t						GetMaxBodySize(std::string host, std::string target) const;
		bool						IsAllowedMethod(std::string host, std::string target, std::string method) const;

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
};

#endif
