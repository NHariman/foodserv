#include "kernel_events.hpp"

# define DEBUG 1

KernelEvents::KernelEvents(std::vector<int> listening_sockets) : _listening_sockets(listening_sockets) {
	if (DEBUG)
		std::cout << "Printing the listening socket fds." << std::endl;
	for (std::vector<int>::iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++) {
		if (DEBUG) std::cout << *it << std::endl;
	}

	KqueueInit();
	KeventInit();
	KernelEventLoop();
}

void	KernelEvents::KqueueInit() {
	_kqueue = kqueue();
	if (_kqueue == -1)
		throw KqueueCreationException();
	if (DEBUG) std::cout << "_kqueue: " << _kqueue << std::endl;
}

/* setting up the structs for all listening sockets */
void	KernelEvents::KeventInit() {
	// create 2 kevent structs
	// 1 struct to register events we want to monitor
	// 1 struct for events to be triggered
	struct kevent	kev_monitor;
	// struct kevent	kev_trigger;

	// initialize the event structure and add it to the kev_monitor 
	// do this for every listening fd
	for (size_t i = 0; i < _listening_sockets.size(); i++) {
		// initialize interest in a read event for the socket
		EV_SET(&kev_monitor, _listening_sockets[i], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
		// add the event in the kqueue
		if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
			throw KeventErrorException();
	}
}

void	KernelEvents::KernelEventLoop() {
	while (true) {

	}
}