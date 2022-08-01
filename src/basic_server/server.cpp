#include "server.hpp"

Server::Server(int port, u_long interface) 
// (int domain, int service, int protocol, int port, u_long interface, int backlog) 
{
    // in here set socket member variable to have the value of an
    // actual socket.
    _socket = new BindingSocket(AF_INET, SOCK_STREAM, 0, port, interface); // Dont forget to delete NEW

    launch();
}

BindingSocket* Server::getSocket() {
    return _socket;
}

void    Server::accepter() {
    std::cout << "goes in accepter" << std::endl;
    // accept connection
    struct sockaddr_in  address = _socket->getAddress();
    int                 addrlen = sizeof(address); 
    _new_socket = accept(_socket->getSocketID(), (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // read connection
    read(_new_socket, buffer, sizeof(buffer));
}

// print out information
void    Server::handler() {
    std::cout << "goes in handler" << std::endl;
    std::cout << buffer << std::endl;
}

void    Server::responder() {
    std::cout << "goes in responder" << std::endl;
    char    *hello = (char*)"Hello from Test Server.";
    write(_new_socket, hello, strlen(hello));
    close(_new_socket);
}

// the infinite loop of waiting accepting and handling requests
void    Server::launch() {
    while (true) {
        std::cout << "==== WAITING =====" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "==== DONE ====" << std::endl;
    }
}

Server::~Server() {
    delete _socket;
}