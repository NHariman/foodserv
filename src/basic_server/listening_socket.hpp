#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

class ListeningSocket {
    
    private:
        int 				_socket_fd;
		const char*			_hostname;
		const char*			_portnumber;
		struct addrinfo*	_addrinfo;
        int                 _addrlen;


    public:
        ListeningSocket(const char *hostname, const char *port);

		void	createListeningSocket();

        int		getListeningSocket();

		void	PrintIpInfo(struct addrinfo *record);

        struct addrinfo*    getAddrInfo();
        int                 getAddrLen();
};

#endif
