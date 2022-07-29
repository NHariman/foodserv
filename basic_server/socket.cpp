#include "socket.hpp"

Socket::Socket(int domain, int port, u_long interface) {
    _addr_struct.sin_family = domain; // AF_INET AF_INET6
    _addr_struct.sin_port = htons(port);
    _addr_struct.sin_addr.s_addr = htonl(interface);

    _sock_fd = socket(domain, SERVICE, 0);

    // check if the FD of _sock_fd is valid, otherwise program is exited.
    checkConnection(_sock_fd);

    bindSocket(_sock_fd, _addr_struct);
}

// int	connectToNetwrok(int sock_fd, struct sockaddr_in addr_struct);

void	Socket::checkConnection(int to_check) {
    if (to_check < 0) {
        perror("Failed to connect: ");
        exit(EXIT_FAILURE);
    }
}

void     Socket::bindSocket(int sock_fd, struct sockaddr_in addr_struct) {
    _connection = bind(sock_fd, (struct sockaddr *)&addr_struct, sizeof(addr_struct));

    // check to see if the bind function went succesfull
    checkConnection(_connection);
}

void	Socket::establishListening() {
	_listening_fd = listen(_sock_fd, BACKLOG);
	checkConnection(_listening_fd);
}

struct sockaddr_in	Socket::getAddress() {
	return (_addr_struct);
}

int		Socket::getSocketFD() {
	return _listening_fd;
}
