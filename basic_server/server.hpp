#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdio.h>
#include <unistd.h>

/*
    is a server a socket, or does a server have a socket. 
    IT HAS A SOCKET, so add that as a member.
*/

#include "Socket.hpp"

class Server {
	protected:
        BindingSocket *_socket; // defines a space in mem to hold a socket. 

        char    buffer[3000];
		int		_new_socket;
    private:
        // child class must create there own
        void accepter();
        void handler();
        virtual void responder();

    public:
        Server(int port, u_long interface);
        // SimpleServer(int domain, int service, int protocol, int port, u_long interface, int backlog);
        // ~SimpleServer();

		virtual	void	launch(); // while loop in child class calling other virtual functions

		BindingSocket*	getSocket();

        // virtual ~SimpleServer();
};

#endif
