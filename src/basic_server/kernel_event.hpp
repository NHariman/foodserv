#ifndef KERNEL_EVENT_HPP
# define KERNEL_EVENT_HPP

#include <vector>
#include <err.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include "listening_socket.hpp"
// #include "../config/nginx_config.hpp"

#define MAX_EVENTS 32
#define MAX_MSG_SIZE 500

class KernelEvent {

	private:
		int		_listening_socket;
	
    public:
        KernelEvent(int sock);

        void	run_event_loop(int kq, int _listening_socket);


		void serveHTML(int s);

		struct client_data {
			int fd;
		} clients[SOMAXCONN];

		int getClientPos(int fd);

		int addNewClientFd(int fd);

		int deleteClientFd(int fd);

		void recv_msg(int s);
};

#endif
