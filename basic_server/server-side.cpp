// Server side C program to demonstrate Socket programming

#include <iostream>
#include <unistd.h> // read write
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

const char html[] = "HTTP/1.1 200 OK\r\n"
"Connection: close\r\n"
"Content-type: text/html\r\n"
"\r\n"
"<html>\r\n"
"<head>\r\n"
"<title>WEBSERV!</title>\r\n"
"</head>\r\n"
"<body>\r\n"
"<h1>Web serv lets goooooo!</h1>\r\n"
"</body>\r\n"
"</html>\r\n\r\n";

int main() {
	int		server_fd;
    int		new_socket;
    long	valread;
    
    // char *hello = "HTTP/1.1 200 OK\r\n Content-Type: text/plain\r\n Content-Length: 20\n\nWebserv is amazing!!";

    /* STEP 1: Creating the socket. */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cerr << "error in creating the socket" << std::endl;
        exit (EXIT_FAILURE);
    }
    
	/* STEP 2: Identifying the socket. */
    struct 	sockaddr_in address;
    int		addrlen = sizeof(address);

	memset((char*)&address, 0, addrlen);
    
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(8080);

	if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
		std::cerr << "error in binding the socket" << std::endl;
		exit (EXIT_FAILURE);
	}
	
	/* STEP 3: Wait for incoming connections on the server */
    if (listen(server_fd, 10) < 0) {
		std::cerr << "error in listen" << std::endl;
		exit (EXIT_FAILURE);
	}

	while(1) {
		printf("\n+++++++ Waiting for new connection ++++++++\n\n");
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
			std::cerr << "error in accepting the connection" << std::endl;
			exit(EXIT_FAILURE);
		}

		/* STEP 4: Send and receive messages */
		char buffer[30000];
		memset(buffer, 0, sizeof(buffer));
		valread = read(new_socket , buffer, 30000);
		std::cout << "THIS IS IN THE RESPONSE:\n " << buffer << std::endl;
		write(new_socket, html, strlen(html));

		/* Close the socket */
		close(new_socket);
	}
	
	// close(server_fd);
	return 0;
}
