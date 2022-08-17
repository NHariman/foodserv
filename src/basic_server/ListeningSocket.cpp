#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(const char *hostname, const char *port) : _hostname(hostname), _portnumber(port) {
	CreateListeningSocket();
}

void	ListeningSocket::CreateListeningSocket() {
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

	_addrlen = sizeof(_addrinfo);

	if (listen(_socket_fd, SOMAXCONN) == -1) {
		perror("listen");
		close(_socket_fd);
		exit (EXIT_FAILURE);
	}
}

int ListeningSocket::getListeningSocket() {
	return _socket_fd;
}

struct addrinfo*	ListeningSocket::getAddrInfo() {
	return _addrinfo;
}

int	ListeningSocket::getAddrLen() {
	return _addrlen;
}

void	ListeningSocket::PrintIpInfo(struct addrinfo *record) {

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