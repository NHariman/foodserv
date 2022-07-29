#include "server.hpp"

Server::Server(int domain, int port, u_long interface) {
	// for now lets use AF_INET domain
	// port 80 and IP 0
    _listening_socket = new Socket(AF_INET, 80, 0);
	launch();
}

void	Server::launch() {
    while (true) {
        std::cout << "==== WAITING =====" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "==== DONE ====" << std::endl;
    }
}

void	Server::accepter() {
	// accept incoming connection
	struct sockaddr_in addr = _listening_socket->getAddress();
	int		addrlen = sizeof(addr);

	_new_socket = accept(_listening_socket->getSocketFD(), (struct sockaddr*)&addr, (socklen_t*)&addrlen);

	read(_new_socket, buffer, sizeof(buffer));

}

void	Server::handler() {
	std::cout << buffer << std::endl;
}

void	Server::responder() {
	char	*hello = "hello from test server.";

	write(_new_socket, hello, strlen(hello));
	close(_new_socket);
}
