#include "Socket.hpp"


BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) {

    // defining address structure
    _address.sin_family = domain;
    // changen byte orders from host to network:
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = htonl(interface);

    // establish socket
    _socket_fd = socket(domain, service, protocol);
    testConnection(_socket_fd);

    // establish binding the socket
    _connection = connectToNetwork(_socket_fd, _address);

    testConnection(getConnection());

    // etablish listening
    _listening = listen(_socket_fd, BACKLOG);
    testConnection(_listening);
}

// tests if the socket function and connection function went through
void    BindingSocket::testConnection(int item_to_test) {
    if (item_to_test < 0) {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
        // change this, maybe to throw an exception
    }
}

int BindingSocket::connectToNetwork(int sock, struct sockaddr_in address) {
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}

struct sockaddr_in BindingSocket::getAddress() {
    return _address;
}

int     BindingSocket::getSocketID() {
    return _socket_fd;
}

int     BindingSocket::getConnection() {
    return _connection;
}

