#include "listening_socket.hpp"
#include "kernel_event.hpp"

int	main() {
	// Socket	ipv4("127.0.0.1", "80");
	// Socket	ipv6("::1", "80");

	// Server	ipv4("0.0.0.0", "80"); // in any address
	// Server	ipv4("127.0.0.1", "12345");

	// Server		ipv6("0000:0000:0000:0000:0000:0000:0000:0001", "12345");
	// http://[::1]:12345/


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