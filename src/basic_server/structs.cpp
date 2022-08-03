/*
	STARTING FILLING THE STRUCTS CORRECTLY

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int	main2() {
	int				status;
	struct addrinfo	hints; // the one you give some information
	struct addrinfo	*servinfo;  // will point to the results

	memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	// hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit (1);
	}

	while (servinfo->ai_next) {
		std::cout << "NEXT" << std::endl;
		servinfo = servinfo->ai_next;
	}

	freeaddrinfo(servinfo); // free the linked-list
}

/*
**	code for a server waiting for connections
**	a stream socket on port 80 on its host IP
**	either IPv4 of IPv6
*/

int	main() {
	int		sockfd;
	struct	addrinfo hints, *servinfo, *p;
	int		returnvalue;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((returnvalue = getaddrinfo("0.0.0.0", "80", &hints, &servinfo)) != 0) {
		std::cout << "getaddrinfo: " << gai_strerror(returnvalue) << std::endl;
		exit(EXIT_FAILURE);
	}

	// looping through results and bind to the first possible one
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("socket");
			continue;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("bind");
			continue ;
		}
		// if we get to this point we must have a connection and no need to loop further
		break ;
	}


	if (p == NULL) {
		// p is at the end of the list, and we do not have a succesfull bind
		std::cout << "failed to bind a single socket" << std::endl;
		freeaddrinfo(servinfo);
	}

}