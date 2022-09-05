
#ifndef NGINX_CONFIG_HPP
# define NGINX_CONFIG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "server_context.hpp"
// #include "location_context.hpp"
// #include "directive_validation/directive_validation.hpp"
// #include "config_utils.hpp"

// Coplien form:

// class A final
// {
//    public:
//       A ();
//       A (const A &a);
//       ~A ();
//       A & operator = (const A &a);
// };

// used for debugging
struct host_target_pair : public std::pair<ServerContext, LocationContext> {
	ServerContext server;
	LocationContext location;
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

		// getters that use host/target pairs to retrieve a very specific value, used for debugging.
		bool						IsSetInHost(std::string host, std::string directive) const;
		bool						IsSetInTarget(std::string host, std::string target, std::string directive) const;
		std::string 				GetRoot(std::string host, std::string target) const;
		std::vector<std::string>	GetIndex(std::string host, std::string target) const;
		size_t						GetMaxBodySize(std::string host, std::string target) const;
		std::vector<ErrorPage>		GetErrorPage(std::string host, std::string target) const;
		bool						GetAutoindex(std::string host, std::string target) const;
		ReturnDir					GetReturn(std::string host, std::string target) const;
		CGIPass						GetCGIPass(std::string host, std::string target) const;
		bool						IsAllowedMethod(std::string host, std::string target, std::string method) const;

		//debugger functions
		host_target_pair			GetHostTargetServer(std::string host, std::string target) const;
<<<<<<< HEAD
		ServerContext				GetHostServer(std::string host) const;
		
		
=======


>>>>>>> 1016e11bf938106516c603cd69321b9884a6c3bc
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
		class HostDoesNotExistException : public std::exception {
			private:
				std::string _err_msg;
			public:
				HostDoesNotExistException(std::string host) {
					_err_msg = "ERROR! requested host: " + host + " was not found.";
				}
				const char *what() const throw() {
					return _err_msg.c_str();
				}
				virtual ~HostDoesNotExistException() throw() {};
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
				virtual ~CannotFindMaxBodySizeException() throw() {};
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
				virtual ~HostTargetPairDoesNotExistException() throw() {}
		};
};

#endif
