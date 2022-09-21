#include "socket.hpp"

# define DEBUG 1

Socket::Socket(std::vector<ServerContext> servers) : _server_contexts(servers) {
	CreateListeningSockets();
}

void	Socket::CreateListeningSockets() {
	_ports_to_bind = FindUniquePorts();
	if (DEBUG) std::cout << "Print Vector of Unique Ports: " << std::endl;
	for (std::vector<std::string>::iterator it = _ports_to_bind.begin(); it != _ports_to_bind.end(); it++) {
		if (DEBUG) std::cout << *it << std::endl;
			_listening_sockets.push_back(CreateSocket(*it));
	}
	if (DEBUG) std::cout << "Printing the listening socket fds." << std::endl;
	for (std::vector<int>::iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++) {
		if (DEBUG) std::cout << *it << std::endl;
	}
}

int	Socket::CreateSocket(std::string port) {
	int		socket_fd;
	int		yes = 1;

	if ((socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw SocketCreationException();
	if ((setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) == -1)
		throw SocketReuseException();

	struct sockaddr_in	sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	// change this, port should maybe not be a string anymore.
	sockaddr.sin_port = htons(atoi(port.c_str()));

	if (::bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1)
		throw BindFailException();
	if (listen(socket_fd, SOMAXCONN)  == -1)
		throw ListenFailException();
	if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1)
		throw FcntlFailException();
	return socket_fd;
}

std::vector<std::string>	Socket::FindUniquePorts() {
	std::vector<std::string>	tmp;
	if (DEBUG) for (std::vector<ServerContext>::const_iterator it = _server_contexts.begin(); it != _server_contexts.end(); it++) {
		std::string	port_num = it->GetPortNumber();
		bool		is_unique = true;
		for (std::vector<std::string>::iterator it2 = tmp.begin(); it2 != tmp.end(); it2++) {
			if (port_num == *it2)
				is_unique = false;
		}
		if (is_unique)
			tmp.push_back(port_num);
	}
	return tmp;
}

std::vector<int>	Socket::GetListeningSockets() const {
	return _listening_sockets;
}

Socket::~Socket() {
	for (std::vector<int>::iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++)
		close(*it);
}
