#include "kernel_events.hpp"

# define DEBUG 1

KernelEvents::KernelEvents(NginxConfig *config_file, std::vector<int> listening_sockets)
	: _config_file(config_file), _listening_sockets(listening_sockets) {
	if (DEBUG)
		std::cout << "Printing the listening socket fds." << std::endl;
	for (std::vector<int>::iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++) {
		if (DEBUG) std::cout << *it << std::endl;
	}

	(void)_config_file;

	KqueueInit();
	KeventInit();
	KernelEventLoop();
}

void	KernelEvents::KqueueInit() {
	_kqueue = kqueue();
	if (_kqueue == -1)
		throw KqueueCreationException();
	if (DEBUG) std::cout << "_kqueue: " << _kqueue << std::endl;
}

/* setting up the structs for all listening sockets */
void	KernelEvents::KeventInit() {
	// create 2 kevent structs
	// 1 struct to register events we want to monitor
	// 1 struct for events to be triggered
	struct kevent	kev_monitor;
	// struct kevent	kev_trigger;

	// this is where we initialize our interest for the read events
	// and register this in our kqueue
	// for every listening socket
	for (size_t i = 0; i < _listening_sockets.size(); i++) {
		EV_SET(&kev_monitor, _listening_sockets[i], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
		if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
			throw KeventErrorException();
	}
}

void	KernelEvents::KernelEventLoop() {
	int				new_events = 0;
	struct kevent	kev_trigger;
	// now we need to use our kevent, to listen for events to be triggered
	// we add them to the triggered event list: kev_trigger
	while (true) {
		new_events = kevent(_kqueue, NULL, 0, &kev_trigger, 1, NULL);
		if (new_events == -1)
			throw KeventErrorException();
		
		// _connection_map has all the client connections
		// _listening_socket has all the socket fildes for the ports
		for (int i = 0; i < new_events; i++) {
			// within the new events there are multiple options
			// 1. the incoming event is a new connection on one of the listening sockets
			// 2. end of file, client can disconnect
			// 3. error with the triggered event
			// 4. an existing client is ready to read
			// 5. an existing client is ready to write
			if (DEBUG) std::cout << "socket fd triggered: " << kev_trigger.ident << std::endl;

			// 1.
			if (InListeningSockets(kev_trigger.ident)) {
				if (DEBUG) std::cout << "Socket fd is in the list of listening sockets.\nWe can accept this client." << std::endl;
				// accept the incoming connection
				int client_fd = AcceptNewConnection(kev_trigger.ident);
				AddToConnectionMap(client_fd);
			}
			else if (kev_trigger.flags & EV_EOF) {
				// disconnect client
				if (DEBUG) std::cout << "In EV_EOF with: " << kev_trigger.ident << std::endl;
				RemoveFromConnectionMap(kev_trigger.ident);
			}
			else if (kev_trigger.flags & EV_ERROR) {
				if (DEBUG) std::cout << "ERROR IN KEVENT" << std::endl;
			}
			else if (kev_trigger.filter == EVFILT_READ) {
				if (DEBUG) std::cout << "its ready to read" << std::endl;
				recv_msg(kev_trigger.ident);
				// recv_msg(kev_trigger.ident);
			}
			else if (kev_trigger.filter == EVFILT_WRITE) {
				if (DEBUG) std::cout << "its ready to write" << std::endl;
			}
			PrintConnectionMap();
		}
	}
}

void	KernelEvents::AddToConnectionMap(int client_fd) {
	// check if this client is already connected
	// this means the client already exists, but has a new request
	// we can delete the complete connection, make a new one with the same fd
	// but then the new request (connection class)
	std::map<int, Connection*>::iterator it = _connection_map.find(client_fd);
	if (it != _connection_map.end()) {
		delete it->second;
		_connection_map.erase(it);
	}
		// delete the connection
	// and delete new Connection blabla

	// add the client
	Connection		*new_conn = new Connection(client_fd, _config_file);
	_connection_map.insert(std::make_pair(client_fd, new_conn));

	// this new client now needs to be added to the kqueue
	// so events on this client will also be triggered
	// first we need to prep a kevent struct to note what events we
	// are interested in, then we need to add this event to the kqueue.
	struct kevent	kev_monitor;
	EV_SET(&kev_monitor, client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
		throw KeventErrorException();
	// serveHTML(client_fd);
}

int		KernelEvents::AcceptNewConnection(int fd) {
    struct sockaddr_in	addr;
    socklen_t 			socklen = sizeof(addr);
	int					client_fd;

	client_fd = accept(fd, (struct sockaddr *)&addr, &socklen);
	if (client_fd == -1)
		throw SocketCreationException();
	return client_fd;
}

void	KernelEvents::RemoveFromConnectionMap(int fd) {
	std::map<int, Connection*>::iterator it = _connection_map.find(fd);
	if (it != _connection_map.end()) {
		delete it->second;
		_connection_map.erase(it);
	}
	close(fd);
}

bool	KernelEvents::InListeningSockets(int fd) const {
	for (std::vector<int>::const_iterator it = _listening_sockets.begin(); it != _listening_sockets.end(); it++) {
		if (*it == fd)
			return true;
	}
	return false;
}

void	KernelEvents::PrintConnectionMap() const {
	std::cout << "Connections fildes in the map: " << std::endl;
	for (std::map<int, Connection*>::const_iterator it = _connection_map.begin(); it != _connection_map.end(); it++)
		std::cout << "client fd: " << it->first << std::endl;
}

// just for check
void KernelEvents::serveHTML(int s) {
    const char *file_path = "/Users/sannealbreghs/Desktop/foodserv/HTML/idex.html";

    char htmlresponse[] = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-type: text/html\r\n"
                    "\r\n";

    std::string		text;
    std::ifstream	read_file(file_path);

    std::vector<char>	buf_vector;

    for (size_t i = 0; i < sizeof(htmlresponse); i++)
        buf_vector.push_back(htmlresponse[i]);

    while (getline(read_file, text)) {
        for (int i = 0; i < int(text.length()); i++) {
            buf_vector.push_back(text[i]);
        }
    }

    char *buf = new char[buf_vector.size()];

    for (size_t i = 0; i < buf_vector.size(); i++) {
        buf[i] = buf_vector.at(i);
    }
    send(s, buf, buf_vector.size(), 0);
    read_file.close();
}

void KernelEvents::recv_msg(int s) {
    char buf[1000];
    int bytes_read = recv(s, buf, sizeof(buf) - 1, 0);
	if (bytes_read != -1) {
	    buf[bytes_read] = 0;
		std::cout << "number of bytes read: " << bytes_read << std::endl;
		std::cout << "*************CLIENT REQUEST*************" << std::endl;
		std::cout << buf << std::endl;
		std::cout << "*************CLIENT REQUEST*************" << std::endl;
		// printf("client message #%d:\n %s", getClientPos(s), buf);
	}
	// dispatch corresponding client_fd match
	for (std::map<int, Connection*>::const_iterator it = _connection_map.begin(); it != _connection_map.end(); it++)
		if (it->first == s) {
			std::cout << "client: " << it->first << std::endl;
			it->second->Receive(buf);
			// after this state its ready to write?
		}
    fflush(stdout);
}