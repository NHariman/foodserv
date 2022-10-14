#ifndef KERNEL_EVENTS_HPP
# define KERNEL_EVENTS_HPP

#include "../connection/connection.hpp"
#include "../config/nginx_config.hpp"

#include <vector>
#include <iostream>
#include <sys/event.h>
#include <utility>
#include <unistd.h>

class KernelEvents {
	private:
		NginxConfig			*_config_file;
		std::vector<int>	_listening_sockets;
		int					_kqueue;

		std::map<int, Connection*>	_connection_map;
	
		void	KqueueInit();
		void	KeventInitListeningSockets();
		bool	InListeningSockets(int fd) const;
		int		AcceptNewConnection(int fd);
		void	AddToConnectionMap(int fd);
		void	RemoveFromConnectionMap(int fd);
		void	PrintConnectionMap() const;
		void	CloseHangingConnections();
		void	ReceiveRequest(int s);
		void	SendResponse(int s);
	
	public:
		KernelEvents(NginxConfig *nginx_config, std::vector<int> listening_sockets);
		void	KernelEventLoop();

	class KqueueCreationException : public std::exception {
	public:
		const char *what() const throw() {
			return "ERROR! Failed to create kqueue.";
		}
	};
	
	class KeventErrorException : public std::exception {
		public:
			const char *what() const throw() {
				return "ERROR! kevent call failed.";
			}
	};

	class SocketCreationException : public std::exception {
		public:
			const char *what() const throw() {
				return "ERROR! Failed to create socket.";
			}
	};

	class RecvException : public std::exception {
		public:
			const char *what() const throw() {
				return "ERROR! Invalid read from recv.";
			}
	};
};

#endif
