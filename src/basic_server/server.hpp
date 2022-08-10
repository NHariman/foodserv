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
#include <sys/poll.h>
#include <sys/ioctl.h>

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
		int			_socket_fd;
		const char*	_hostname;
		const char*	_portnumber;
		struct addrinfo* _addrinfo;

		Server();

	public:


		Server(const char *hostname, const char* port);

		void	CreateListeningSocket();

		void	ListeningForConnections();

		void	PrintIpInfo(struct addrinfo *record) {

			void	*addr;
			char	*ipversion;
			char	ipstr[INET6_ADDRSTRLEN];

			// check IP version
			if (record->ai_family == AF_INET) {
				struct sockaddr_in	*ipv4 = (struct sockaddr_in*)record->ai_addr;
				addr = &(ipv4->sin_addr);
				ipversion = (char *)"IPv4";
			}
			else {
				struct sockaddr_in6	*ipv6 = (struct sockaddr_in6*)record->ai_addr;
				addr = &(ipv6->sin6_addr);
				ipversion = (char *)"IPv6";
			}

			inet_ntop(record->ai_family, addr, ipstr, sizeof(ipstr));
			std::cout << ipversion << " : " << ipstr << std::endl;
		}

};

#endif
