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

	
	// vars needed from the listening socket class
	int					_listening_socket;
	int					_addrlen;
	struct addrinfo*	_addrinfo;

	// vars needed for the kernel event
	int				_kq; // list of events we are interested in
	struct kevent	_event_to_monitor; // event set for READ's on listen
	// struct kevent	_event_to_monitor;
	struct kevent	_event_list[SOMAXCONN];

	// an array of client socket fd's
	// set them to 0 to start with
	struct client_fds {
		int	fd;
	} _clients[SOMAXCONN];

	KernelEvent();
	

public:
	KernelEvent(int sock, struct addrinfo* addrinfo, int addrlen);
	
	// initialize kqueue
	// kqueue holds all the events we are interested in
	// step 1: creating an empty kqueue
	void	initKqueue();

	// STEP 2: creating the event set for reads on the socket

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
		EV_SET(&_event_to_monitor, _listening_socket, EVFILT_READ | EV_CLEAR, EV_ADD, 0, /*SOMAXCONN*/ 0, NULL);
		// if (kevent(_kq, &_event_to_monitor, 1, NULL, 0, NULL) == -1) {
		// 	perror("kevent");
		// 	exit (EXIT_FAILURE);
		// } 
		if (kevent(_kq, &_event_to_monitor, 1, NULL, 0, NULL) == -1) {
			perror("kevent");
			exit (EXIT_FAILURE);
		}
	}

	void	keventLoop() {
		int	num_events;
		int	client_fd;

		while (true) {
			if ((num_events = kevent(_kq, &_event_to_monitor, 0, _event_list, SOMAXCONN, NULL)) == -1) {
				perror("kevent deze");
				exit (EXIT_FAILURE);
			}

			for (int i = 0; i < num_events; i++) {
				std::cout << num_events << std::endl;
				if (_event_list[i].ident == _listening_socket) {
					std::cout << "in eerste if"<< std::endl; 
					if ((client_fd = accept(_event_list[i].ident, (struct sockaddr*)&_addrinfo, (socklen_t *)&_addrlen)) == -1) {
						perror("accept");
						exit (EXIT_FAILURE);
					}

					//
					char HTTPREQUEST[1000];
					memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
					std::cout << "Amount read by recv: " << recv(client_fd, HTTPREQUEST, sizeof(HTTPREQUEST), 0) << std::endl;
					std::cout << HTTPREQUEST << std::endl;
					//

					if (addClientFd(client_fd) == 0) {
						EV_SET(&_event_to_monitor, client_fd, EVFILT_READ | EV_CLEAR, EV_ADD, 0, 0, NULL);
						kevent(_kq, &_event_to_monitor, 1, NULL, 0, NULL);
						send(client_fd, html, sizeof(html), 0);
					}
					else {
						// send the error correct error message
						std::cout << "connection refused." << std::endl;
						close (client_fd);
					}
				}
				else if (_event_list[i].flags & EV_EOF) {
					std::cout << "in tweede if"<< std::endl; 
					std::cout << "client disconnected: #" << findClientFd(_event_list[i].ident) << std::endl;
					EV_SET(&_event_to_monitor, _event_list[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
					kevent(_kq, &_event_to_monitor, 1, NULL, 0, NULL);
					deleteLostConnections(_event_list[i].ident);
				}
				else if (_event_list[i].filter == EVFILT_READ) {
					std::cout << "in derde if"<< std::endl; 
					recv_msg(_event_list[i].ident);
				}
			}
		}
	}

	// delete after
	void recv_msg(int s) {
		char buf[1000];
		int bytes_read = recv(s, buf, sizeof(buf) - 1, 0);
		buf[bytes_read] = 0;
		printf("client #%d: %s", findClientFd(s), buf);
		fflush(stdout);
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
