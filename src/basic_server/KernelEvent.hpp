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
		int				_kq; // list of events we are interested in
		int				_listening_socket;
		struct kevent	_event_to_monitor; // event set for READ's on the listening socket
		struct kevent	_event_to_trigger;
		struct kevent	_event_list[SOMAXCONN];

		const int		_addrlen = _ListenSocketClass.getAddrLen();
		struct addrinfo*	_addrinfo = _ListenSocketClass.getAddrInfo();
		ListeningSocket		_ListenSocketClass;
		// ListeningSocket	test("::", "12345");
		

		// an array of client socket fd's
		// set them to 0 to start with
		struct client_fds {
			int	fd;
		} _clients[SOMAXCONN];
		

	public:
		KernelEvent();
		
		// initialize kqueue
		// kqueue holds all the events we are interested in
		// step 1: creating an empty kqueue
		void	initKqueue();

		// STEP 2: creatomg the event set for reads on the socket

		// kevent is identified by a <ident, filter> pair where ident
		// can be a fildes and filter is the kernel filter used to process
		// the respective event: EVFILT_READ, which are triggered when data
		// exists for reading.

		// EVENT_SET = EVENTS WE WANT TO MONITOR
	    // use EV_SET to fill the kevent structure
		// set the ident to the _listening_socket
		// changelist.ident = _listening_socket;
		// and the flag to EV_ADD as you want to add it to the kqueue
		// changelist.flag = EV_ADD;
		// set filter on EVFILT_READ as you only want to add when read is possible
		// changelist.filter = EVFILT_READ;
		void	createEventSetMonitor() {
			EV_SET(&_event_to_monitor, _listening_socket, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR, 0, SOMAXCONN, NULL);
			if (kevent(_kq, &_event_to_monitor, 1, NULL, 0, NULL) == -1) {
				perror("kevent");
				exit (EXIT_FAILURE);
			} 
		}

		void	keventLoop() {
			while (true) {

			}
		}

		int		findClientFd(int fd);

		// for a new connection (request) add in the fd in the _clients array
		// the place to store is is the first fd == 0
		int	addClientFd(int fd);

		// when a connection is lost, we dont want that client_fd to stay
		// in the array of _clients fd's
		int	deleteLostConnections(int fd);
};

#endif
