/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The class NginxConfig parses the configuration
   file given as argument.
*/

#include "server.hpp"

Server::Server(const char *hostname, const char *port) : _hostname(hostname), _portnumber(port) {
	CreateListeningSocket();
	ListeningForConnections();
}

void	Server::CreateListeningSocket() {
	struct 	addrinfo hints;
	struct 	addrinfo *results;
	int		yes = 0;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if ((getaddrinfo(_hostname, _portnumber, &hints, &results)) != 0) {
		perror("getaddrinfo");
		exit (EXIT_FAILURE);
	}

	for (_addrinfo = results; _addrinfo != NULL; _addrinfo = results->ai_next) {
		if ((_socket_fd = socket(_addrinfo->ai_family, _addrinfo->ai_socktype, _addrinfo->ai_protocol)) == -1)
			continue ; // to to next iteration
		if ((setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) == -1) {
			perror("setsockopt");
			exit (EXIT_FAILURE);
		}
		if (bind(_socket_fd, _addrinfo->ai_addr, _addrinfo->ai_addrlen) != -1)
			break ;  // break out of loop when socket is succesfully binded
		// if the for loops gets to this point, the socket is not able to bind and we go to the next iteration
		// we need to close the socket which was unable to bind before doing this.
		close (_socket_fd);
	}
	free(results);

	// an extra to print the IP
	// PrintIpInfo(_addrinfo);

	if (_addrinfo == NULL) {
		std::cout << "Failed to create and bind a socket..." << std::endl;
		exit (EXIT_FAILURE);
	}

	if (listen(_socket_fd, SOMAXCONN) == -1) {
		perror("listen");
		close(_socket_fd);
		exit (EXIT_FAILURE);
	}
}

void	Server::ListeningForConnections() {
	while (true) {
	
		
		std::cout << "\n+++++++ Waiting for new connection ++++++++\n" << std::endl;

		int addrlen = sizeof(_addrinfo);
		int accept_fd;
		
		if ((accept_fd = accept(_socket_fd, (struct sockaddr*)&_addrinfo, (socklen_t*)&addrlen)) < 0) {
			perror("accept");
			exit (EXIT_FAILURE);
		}


		char buf[30000];
		memset(buf, 0, sizeof(buf));

		std::cout << "THIS IS IN THE RESPONSE" << std::endl;
		int bytes_send = send(accept_fd, html, sizeof(html), 0);
		std::cout << html << std::endl;

		// this has to be a whole function on its own
		if (bytes_send != sizeof(html)) {
			std::cout << "Not the whole message has been send over" << std::endl;
			if (bytes_send == -1) {
				perror("send");
				exit (EXIT_FAILURE);
			}
		}


		write(accept_fd, html, strlen(html));

		recv(accept_fd, buf, sizeof(buf), 0);
		std::cout << "THIS IS IN THE REQUEST:\n" << buf << std::endl;
		close(accept_fd);
	}
}