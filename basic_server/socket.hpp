#ifndef SOCKET_HPP
# define SOCKET_HPP
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define BACKLOG 3

/*
	This class implements a call to the bind() function
	of sockets as a definition of the connectToNetwork() 
	virtual function from class SimpleSocket
*/

// #include "SimpleSocket.hpp"

class BindingSocket {
	private:
		struct	sockaddr_in	_address;
		int		_socket_fd;
		int		_connection;
		int		_listening;

	private:
		BindingSocket();
	public:
		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
		
		// bind function
		int	connectToNetwork(int sock, struct sockaddr_in address);

		void	testConnection(int);
		struct	sockaddr_in	getAddress();
		int		getSocketID();
		int		getConnection();
		void	setConnection();

};

// class BindingSocket : public SimpleSocket {
// 	private:
// 		BindingSocket();
// 	public:
// 		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
// 		// override virtual functions
// 		int connectToNetwork(int sock, struct sockaddr_in address);
// };

#endif