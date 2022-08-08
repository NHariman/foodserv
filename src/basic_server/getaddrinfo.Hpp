#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

static const char html[] = "HTTP/1.1 200 OK\r\n"
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


class Socket {

	private:
		int			_socket_fd;
		const char*	_hostname;
		const char*	_portnumber;
		// check if this works for accept address
		struct addrinfo*	_record;

		Socket();

	public:
		Socket(const char *hostname, const char *port) : _hostname(hostname), _portnumber(port) {
			CreateAndBindSocket();
			ListenAndAccept();
			// listen(_socket_fd, SOMAXCONN);
		}

		void	CreateAndBindSocket() {
			std::cout << "in getaddrinfo()" << std::endl;

			struct	addrinfo	hints;
			struct	addrinfo	*results;
			// struct	addrinfo	*record;

			int		yes = 1;

			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			if ((getaddrinfo(_hostname, _portnumber, &hints, &results)) != 0) {
				perror("getaddrinfo");
				exit (EXIT_FAILURE);
			}

			// loop through the results and try to set up a socket with the guesses
			for (_record = results; _record != NULL; _record = results->ai_next) {
				std::cout << "IN FOR LOOP" << std::endl;
				_socket_fd = socket(_record->ai_family, _record->ai_socktype, _record->ai_protocol);
				if (_socket_fd == -1)
					continue ; // go to the next iteration

				// if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) < 0) {
				// 	perror("fcntl");
				// }

				if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
					perror("setsockopt");
					exit (EXIT_FAILURE);
				}
				if (bind(_socket_fd, _record->ai_addr, _record->ai_addrlen) != -1)
					break ;
				close (_socket_fd);
			}

			if (_record == NULL) {
				std::cout << "Failed to create and bind a socket." << std::endl;
				exit (EXIT_FAILURE);
			}

			PrintIpInfo(_record);
			
			free(results);
		}

		void	ListenAndAccept() {
			struct sockaddr_storage _accept_addrxw;

			std::cout << "max connections for listen: " << SOMAXCONN << std::endl;
			if (listen(_socket_fd, SOMAXCONN) == -1) {
				perror("listen");
				exit (EXIT_FAILURE);
			}

			// now accept incoming connections
			while (1) {

				std::cout << "\n+++++++ Waiting for new connection ++++++++\n" << std::endl;

				int addrlen = sizeof(_record);
				int accept_fd;
				
				if ((accept_fd = accept(_socket_fd, (struct sockaddr*)&_record, (socklen_t*)&addrlen)) < 0) {
					perror("accept");
					exit (EXIT_FAILURE);
				}


				// if (fcntl(accept_fd, F_SETFL, O_NONBLOCK) < 0) {
				// 	perror("fcntl");
				// 	exit (EXIT_FAILURE);
				// }

				char buf[30000];
				// memset(buffer, 0, sizeof(buffer));

				int bytes_send = send(accept_fd, html, sizeof(html), 0);
				std::cout << html << std::endl;

				// this has to be a whole function on its own
				if (bytes_send != sizeof(html)) {
					std::cout << "Not the whole message has been send over" << std::endl;
					if (bytes_send == -1) {
						perror("send");
						exit (EXIT_FAILURE);
					}
				}

				write(accept_fd, html, strlen(html));


				recv(accept_fd, buf, sizeof(buf), 0);
				std::cout << "THIS IS IN THE REQUEST:\n" << buf << std::endl;
				close(accept_fd);
			}
			

		}

		void	PrintIpInfo(struct addrinfo *record) {

			void	*addr;
			char	*ipversion;
			char	ipstr[INET6_ADDRSTRLEN];

			// check IP version
			if (record->ai_family == AF_INET) {
				struct sockaddr_in	*ipv4 = (struct sockaddr_in*)record->ai_addr;
				addr = &(ipv4->sin_addr);
				ipversion = (char *)"IPv4";
			}
			else {
				struct sockaddr_in6	*ipv6 = (struct sockaddr_in6*)record->ai_addr;
				addr = &(ipv6->sin6_addr);
				ipversion = (char *)"IPv6";
			}

			inet_ntop(record->ai_family, addr, ipstr, sizeof(ipstr));
			std::cout << ipversion << " : " << ipstr << std::endl;
		}

};