#include "kernel_events.hpp"

# define DEBUG 1

KernelEvents::KernelEvents(std::vector<int> listening_sockets) : _listening_sockets(listening_sockets) {
	if (DEBUG)
		std::cout << "Printing the listening socket fds." << std::endl;
	for (std::vector<int>::iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++) {
		if (DEBUG) std::cout << *it << std::endl;
	}

	KqueueInit();
}

void	KernelEvents::KqueueInit() {
	_kqueue = kqueue();
	if (_kqueue == -1)
		throw KqueueCreationException();
	if (DEBUG) std::cout << "_kqueue: " << _kqueue << std::endl;
}