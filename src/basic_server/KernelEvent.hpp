#ifndef KERNEL_EVENT_HPP
#define KERNEL_EVENT_HPP

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h> // we dont do time, so get rid of this?
#include <iostream>
#include <netdb.h>
#include <unistd.h>

#include "ListeningSocket.hpp"

class KernelEvent {

	private:
		int		_kq; // list of events we are interested in
		int		_listening_socket;

		// ListeningSocket	test("::", "12345");
		ListeningSocket		_ListenSocketClass;

		struct client_fds {
			int	fd;
		} _clients[SOMAXCONN];
		

	public:
		KernelEvent();
		

		// working with the connectoins
		// use an array of client socket fd's
		// and set them all to 0 to start with

		// given an FD find the correspoding client data
		int	findClientFd(int fd) {
			for (int i = 0; i < SOMAXCONN; i++) {
				if (_clients[i].fd == fd)
					return 1;
			}
			// if no matching ID is found return -1
			return -1;
		}

		// for a new connection (request) add in the fd in the _clients array
		// the place to store is is the first fd == 0
		int	addClientFd(int fd) {
			// return -1 on an invalid fd
			if (fd < 1)
				return -1;
			int	i;
			// looks for the position of the first empty spot
			i = findClientFd(0);
			if (i == -1)
				return -1;
			_clients[i].fd = fd;
			return 0;
		}

		// when a connection is lost, we dont want that client_fd to stay
		// in the array of _clients fd's
		int	deleteLostConnections(int fd) {
			if (fd < 1)
				return -1;
			int i;
			// find position in the array where to delete
			i = findClientFd(fd);
			if (i == -1)
				return -1;
			_clients[i].fd = 0;
			if (close(fd) == -1)
				return -1;
			return 0;
		}
};

#endif
