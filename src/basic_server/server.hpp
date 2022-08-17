/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The Server class is the ..
*/

#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/event.h>

struct client_data {
	int fd;
};

static const char html[] = "HTTP/1.1 200 OK\r\n"
							"Connection: close\r\n"
							"Content-type: text/html\r\n"
							"\r\n"
							"<html>\r\n"
							"<head>\r\n"
							"<title>WEBSERV!</title>\r\n"
							"</head>\r\n"
							"<body>\r\n"
							"<h1>Web serv lets goooooo!</h1>\r\n"
							"</body>\r\n"
							"</html>\r\n\r\n";


class Server {

	private:
		int					_socket_fd;
		const char*			_hostname;
		const char*			_portnumber;
		struct addrinfo*	_addrinfo;
		client_data			_clients[SOMAXCONN];

		Server();

	public:


		Server(const char *hostname, const char* port);

		void	CreateListeningSocket();

		void	ListeningForConnections();

		void	KQ();

		int		GetConnection(int);

		int		AddConnection(int);

		int		DeleteConnection(int);

		void	eventLoop(int, int);

		void	PrintIpInfo(struct addrinfo *record);

};

#endif
