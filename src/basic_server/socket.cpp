#include "socket.hpp"

BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) {

    // // defining address structure
    // _address.sin_family = domain;
    // // changen byte orders from host to network:
    // _address.sin_port = htons(port);
    // _address.sin_addr.s_addr = htonl(interface);

    // // establish socket
    // _socket_fd = socket(domain, service, protocol);
    (void)protocol;
    (void)port;

    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = domain;
    hints.ai_socktype = service;

    std::cout << "INTERFACE:" << interface << std::endl;

    rv = getaddrinfo("0.0.0.0", "80", &hints, &servinfo); // get these first two values from the class server.
    testConnection(rv);

	// looping through results and bind to the first possible one
	for (p = servinfo; p != NULL; p = p->ai_next) {
        memset(&p, 0, sizeof(p));
		if ((_socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		if (bind(_socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(_socket_fd);
			perror("bind");
			continue ;
		}
		// if we get to this point we must have a connection and no need to loop further
		break ;
	}

    if (p == NULL) {
        // p is at the end of the list, and we do not have a succesfull bind
        std::cout << "failed to bind a single socket" << std::endl;
        freeaddrinfo(servinfo);
    }

    // CONTINUE HERE

    // testConnection(_socket_fd);

    // // establish binding the socket
    // _connection = connectToNetwork(_socket_fd, _address);

    // testConnection(getConnection());

    // etablish listening
    testConnection(listen(_socket_fd, BACKLOG));
}

// tests if the socket function and connection function went through
void    BindingSocket::testConnection(int item_to_test) {
    if (item_to_test < 0) {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
        // change this, maybe to throw an exception
    }
}

// Once you have a socket, you can associate that socket with a port on your local machine.
// The port number is used by the kernel to match an incoming packet to a certain process's socket descriptor.
int BindingSocket::connectToNetwork(int sock, struct sockaddr_in address) {
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}

struct sockaddr_in BindingSocket::getAddress() {
    return _address;
    // return (struct sockaddr_in*)&p->ai_addr;
}

int     BindingSocket::getSocketID() {
    return _socket_fd;
    // return _listening;
}

int     BindingSocket::getConnection() {
    return _connection;
}

