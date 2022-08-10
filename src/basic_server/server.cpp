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
	// ListeningForConnections();
	KQ();
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
		// if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1) {
		// 	perror("fcntl");
		// 	exit (EXIT_FAILURE);
		// }
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

void	Server::KQ() {
	// create an empty KQ
	int	kq = kqueue();

	// create an events set for reads on sockets
	struct kevent evSet;
	// read in more on EV_SET
	EV_SET(&evSet, _socket_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &evSet, 1, NULL, 0, NULL);
	
	// loop function where we handle incomming connections and send/receive messages
	eventLoop(kq, _socket_fd);
	std::cout << "SUCCES";
	exit (EXIT_SUCCESS);
}

/*
Every time we receive a new connection, we accept the connection, accept() does the tcp 3-way handshake
and creates a socket for further communication with that client, and returns the fd of that socket.
We need to store the fd of all connected client so we can communicate with them
*/

/* CONNECTION POOLING */

// function that gets the finds the corresponding client_data struct by iterating over the array
int		Server::GetConnection(int fd) {
	for (int i = 0; i < SOMAXCONN; i++) {
		if (_clients[i].fd == fd)
			return i;
		return -1;
	}
}

int		Server::AddConnection(int fd) {
	if (fd < 1)
		return -1;
	// gets the position of the first empty fd
	int i = GetConnection(0);
	_clients[i].fd = fd;
	return 0;
}

int		Server::DeleteConnection(int fd) {
	if (fd < 1)
		return -1;
	int i = GetConnection(fd);
	if (i == -1)
		return -1;
	_clients[i].fd = 0;
	close(fd);
	return 0;
}


// an infinite loop where incomings events are received and processed
void	Server::eventLoop(int kq, int sock) {
	struct kevent evList[SOMAXCONN];
	struct kevent evSet;
	int num_events = kevent(kq, NULL, 0, evList, SOMAXCONN, NULL);
	int addrlen = sizeof(_addrinfo);

	while (true) {
		std::cout << "\n+++++++ Waiting for new connection ++++++++\n" << std::endl;
		for (int i = 0; i < num_events; i++) {
			// receive incoming connections
			if (evList[i].ident == _socket_fd) {
				int fd = accept(evList[i].ident, (struct sockaddr*)&_addrinfo, (socklen_t*)&addrlen);
				if (AddConnection(fd) == 0) {
					EV_SET(&evSet, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
					kevent(kq, &evSet, 1, NULL, 0, NULL);
					send(fd, html, sizeof(html), 0);
				}
				else if (evList[i].flags & EV_EOF) {
					std::cout << "No more connection";
					close(fd);
				}
				else if (evList[i].filter == EVFILT_READ) {
					char buf[200];
					int bytes_read = recv(evList[i].ident, buf, sizeof(buf) - 1, 0);
					buf[bytes_read] = 0;
					std::cout << "client #" << i << GetConnection(evList[i].ident) << std::endl;
				}
			}
		}
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

void	Server::PrintIpInfo(struct addrinfo *record) {

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