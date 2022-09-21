#include "listening_socket.hpp"
#include "kernel_event.hpp"

int	main() {

	// ListeningSocket *ipv6 = new ListeningSocket("::", "12345"); // in any address
	// add in exceptions, if this does not return a valid listening socket, DO NOT continue.
	
	// std::cout << "LISTENING SOCKET: "<< ipv6->getListeningSocket() << std::endl;

	// now initialize the kqueue with the newly opened listening socket.
	ListeningSocket	*sock = new ListeningSocket("0", "8080");
	KernelEvent	*webserver = new KernelEvent(sock->getListeningSocket());

	// delete ipv6;
	delete sock;
	delete webserver;

}