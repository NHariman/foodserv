/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The class ....
*/

#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define SERVICE SOCK_STREAM // always the same, we only use tcp
#define BACKLOG 3

class Socket {
	private:
		struct 	sockaddr_in	_addr_struct;
		int		_sock_fd;
		int		_connection;
		int		_listening_fd;

		Socket();

	public:
		Socket(int domain, int port, u_long interface);

		void	bindSocket(int sock_fd, struct sockaddr_in addr_struct);

		void	checkConnection(int to_check);
		void	establishListening();
		struct sockaddr_in	getAddress();
		int		getSocketFD();

};

#endif