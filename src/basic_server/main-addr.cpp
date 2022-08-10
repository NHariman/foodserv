#include "server.hpp"

int	main() {
	// Socket	ipv4("127.0.0.1", "80");
	// Socket	ipv6("::1", "80");

	// Server	ipv4("0.0.0.0", "80"); // in any address
	// Server	ipv4("127.0.0.1", "12345");
	Server	ipv6("::", "12345"); // in any address

	// Server		ipv6("0000:0000:0000:0000:0000:0000:0000:0001", "12345");
	// http://[::1]:12345/

}