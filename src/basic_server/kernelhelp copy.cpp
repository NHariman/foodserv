#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ListeningSocket.hpp"


// #define NUM_CLIENTS
#define MAX_EVENTS 32
#define MAX_MSG_SIZE 500

// struct kevent evSet;

// struct client_data {
//     int fd;
// } clients[SOMAXCONN];

// int getClientPos(int fd) {
//     for (int i = 0; i < SOMAXCONN; i++)
//         if (clients[i].fd == fd)
//             return i;
//     return -1;
// }

// int addNewClientFd(int fd) {
//     if (fd < 1) return -1;
//     int i = getClientPos(0);
//     if (i == -1) return -1;
//     clients[i].fd = fd;
//     return 0;
// }

// int deleteClientFd(int fd) {
//     if (fd < 1) return -1;
//     int i = getClientPos(fd);
//     if (i == -1) return -1;
//     clients[i].fd = 0;
//     return close(fd);
// }

// void recv_msg(int s) {
//     char buf[MAX_MSG_SIZE];
//     int bytes_read = recv(s, buf, sizeof(buf) - 1, 0);
//     buf[bytes_read] = 0;
//     printf("client message #%d:\n %s", getClientPos(s), buf);
//     fflush(stdout);
// }

// void serveHTML(int s) {
//     char msg[80];
//     send(s, html, sizeof(html), 0);
// }

// void run_event_loop(int kq, int _listening_socket) {
//     struct kevent evSet;
//     struct kevent evList[MAX_EVENTS];
//     struct sockaddr_storage addr;
//     socklen_t socklen = sizeof(addr);

//     while (1) {
//         int num_events = kevent(kq, NULL, 0, evList, MAX_EVENTS, NULL);
//         for (int i = 0; i < num_events; i++) {
//             // receive new connection
//             if (evList[i].ident == _listening_socket) {
//                 int fd = accept(evList[i].ident, (struct sockaddr *) &addr, &socklen);
//                 if (addNewClientFd(fd) == 0) {
//                     EV_SET(&evSet, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
//                     kevent(kq, &evSet, 1, NULL, 0, NULL);
//                     serveHTML(fd);
//                 } else {
//                     printf("connection refused.\n");
//                     close(fd);
//                 }
//             } // client disconnected
//             else if (evList[i].flags & EV_EOF) {
//                 int fd = evList[i].ident;
//                 printf("client #%d disconnected.\n", getClientPos(fd));
//                 EV_SET(&evSet, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
//                 kevent(kq, &evSet, 1, NULL, 0, NULL);
//                 deleteClientFd(fd);
//             } // read message from client
//             else if (evList[i].filter == EVFILT_READ) {
//                 recv_msg(evList[i].ident);
//                 // EV_SET()
//             }
//         }
//     }
// }

// // int create_socket_and_listen() {
// //     struct addrinfo *addr;
// //     struct addrinfo hints;
// //     memset(&hints, 0, sizeof hints);
// //     hints.ai_flags = AI_PASSIVE;
// //     hints.ai_family = PF_UNSPEC;
// //     hints.ai_socktype = SOCK_STREAM;
// //     getaddrinfo("127.0.0.1", "8080", &hints, &addr);
// //     int _listening_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
// //     bind(_listening_socket, addr->ai_addr, addr->ai_addrlen);
// //     listen(_listening_socket, SOMAXCONN);
// //     return _listening_socket;
// // }

// int main() {
//     // int _listening_socket = create_socket_and_listen();
//     ListeningSocket *sock = new ListeningSocket("127.0.0.1", "12345");

//     int _listening_socket = sock->getListeningSocket();
//     int kq = kqueue();
//     struct kevent evSet;
//     EV_SET(&evSet, _listening_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
//     kevent(kq, &evSet, 1, NULL, 0, NULL);
//     run_event_loop(kq, _listening_socket);
//     return EXIT_SUCCESS;
// }

class KernelEvent {

	private:
		int		_listening_socket;
	
    public:
        KernelEvent(int sock) : _listening_socket(sock) {
            // ListeningSocket *sock = new ListeningSocket("127.0.0.1", "12345");
            // int _listening_socket = sock->getListeningSocket();
            int kq = kqueue();
            struct kevent evSet;
            EV_SET(&evSet, _listening_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
            kevent(kq, &evSet, 1, NULL, 0, NULL);
            run_event_loop(kq, _listening_socket);
            // return EXIT_SUCCESS; 
        }

        void	run_event_loop(int kq, int _listening_socket) {
			struct kevent evSet;
			struct kevent evList[MAX_EVENTS];
			struct sockaddr_storage addr;
			socklen_t socklen = sizeof(addr);

			while (1) {
				int num_events = kevent(kq, NULL, 0, evList, MAX_EVENTS, NULL);
				for (int i = 0; i < num_events; i++) {
					// receive new connection
					if (evList[i].ident == _listening_socket) {
						int fd = accept(evList[i].ident, (struct sockaddr *) &addr, &socklen);
						if (addNewClientFd(fd) == 0) {
							EV_SET(&evSet, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
							kevent(kq, &evSet, 1, NULL, 0, NULL);
							serveHTML(fd);
						} else {
							printf("connection refused.\n");
							close(fd);
						}
					} // client disconnected
					else if (evList[i].flags & EV_EOF) {
						int fd = evList[i].ident;
						printf("client #%d disconnected.\n", getClientPos(fd));
						EV_SET(&evSet, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
						kevent(kq, &evSet, 1, NULL, 0, NULL);
						deleteClientFd(fd);
					} // read message from client
					else if (evList[i].filter == EVFILT_READ) {
						recv_msg(evList[i].ident);
						// EV_SET()
					}
				}
			}	
		}

		void serveHTML(int s) {
			char msg[80];
			send(s, html, sizeof(html), 0);
		}

		struct client_data {
			int fd;
		} clients[SOMAXCONN];

		int getClientPos(int fd) {
			for (int i = 0; i < SOMAXCONN; i++)
				if (clients[i].fd == fd)
					return i;
			return -1;
		}

		int addNewClientFd(int fd) {
			if (fd < 1) return -1;
			int i = getClientPos(0);
			if (i == -1) return -1;
			clients[i].fd = fd;
			return 0;
		}

		int deleteClientFd(int fd) {
			if (fd < 1) return -1;
			int i = getClientPos(fd);
			if (i == -1) return -1;
			clients[i].fd = 0;
			return close(fd);
		}

		void recv_msg(int s) {
			char buf[MAX_MSG_SIZE];
			int bytes_read = recv(s, buf, sizeof(buf) - 1, 0);
			buf[bytes_read] = 0;
			printf("client message #%d:\n %s", getClientPos(s), buf);
			fflush(stdout);
		}
};

int		main() {
	ListeningSocket	*sock = new ListeningSocket("::", "8080");
	KernelEvent *check = new KernelEvent(sock->getListeningSocket());
}