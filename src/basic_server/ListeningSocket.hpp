#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

static const char html[] = "HTTP/1.1 200 OK\r\n"
							"Connection: close\r\n"
							"Content-type: text/html\r\n"
							"\r\n";
							// "<html>\r\n"
							// "<head>\r\n"
							// "<title>WEBSERV!</title>\r\n"
							// "</head>\r\n"
							// "<body>\r\n"
							// "<h1>Web serv lets goooooo!</h1>\r\n"
							// "</body>\r\n"
							// "</html>\r\n\r\n";


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
        const char*         getHTML();
};

#endif
