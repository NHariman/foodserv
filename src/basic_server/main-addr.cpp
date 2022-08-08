#include "getaddrinfo.hpp"

int	main() {
	// Socket	ipv4("127.0.0.1", "80");
	// Socket	ipv6("::1", "80");

	Socket	ipv4("0.0.0.0", "80"); // in any address
	Socket	ipv6("::", "80"); // in any address
}