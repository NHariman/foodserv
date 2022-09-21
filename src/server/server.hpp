#ifndef SERVER_HPP
# define SERVER_HPP

#include "../config/nginx_config.hpp"
#include "../config/server_context.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

class Server {
	private:
		std::vector<ServerContext>	_server_contexts;
		std::vector<int>			_listening_sockets;
		std::vector<std::string>	_ports_to_bind;

		std::vector<std::string>	FindUniquePorts();
		void						CreateListeningSockets();
		int							CreateSocket(std::string port);

	public:
		Server(std::vector<ServerContext> servers_contexts);
		~Server();

	
		class SocketCreationException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Failed to create socket.";
				}
		};
		class SocketReuseException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Setsockopt function failed.";
				}
		};
		class BindFailException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! A socket failed to bind.";
				}
		};
		class ListenFailException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Listen function failed.";
				}
		};
		class FcntlFailException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Listen function failed.";
				}
		};
};

#endif
