#include "kernel_events.hpp"

# define DEBUG 0
# define MAX_EVENTS 128

#include "../request/request.hpp"
#include "../resolved_target/target_config.hpp"

KernelEvents::KernelEvents(NginxConfig *config_file, std::vector<int> listening_sockets)
	: _config_file(config_file), _listening_sockets(listening_sockets) {
	KqueueInit();
	KeventInitListeningSockets();
}

void	KernelEvents::KqueueInit() {
	_kqueue = kqueue();
	if (_kqueue == -1)
		throw KqueueCreationException();
}

void	KernelEvents::KeventInitListeningSockets() {
	struct kevent	kev_monitor;

	for (size_t i = 0; i < _listening_sockets.size(); i++) {
		EV_SET(&kev_monitor, _listening_sockets[i], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
		if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
			throw KeventErrorException();
	}
}

void	KernelEvents::KernelEventLoop() {
	int				new_events = 0;
	struct kevent	kev_trigger[MAX_EVENTS];

	// now we need to use our kevent, to listen for events to be triggered
	// we add them to the triggered event list: kev_trigger
	while (true) {
		new_events = kevent(_kqueue, NULL, 0, kev_trigger, 100, NULL);
		if (new_events == -1)
			throw KeventErrorException();

		if (DEBUG) std::cout << "Num events: " << new_events << std::endl;
		
		// _connection_map has all the client connections
		// _listening_socket has all the socket fildes for the ports
		for (int i = 0; i < new_events; i++) {
			if (DEBUG) std::cout << "socket fd triggered: " << kev_trigger[i].ident << std::endl;
			if (kev_trigger[i].flags & EV_ERROR)
				throw KeventErrorException();
			else if (kev_trigger[i].flags & EV_EOF) {
				if (DEBUG) std::cout << "In EV_EOF with: " << kev_trigger[i].ident << std::endl;
				RemoveFromConnectionMap(kev_trigger[i].ident);
			}
			else if (InListeningSockets(kev_trigger[i].ident)) {
				if (DEBUG) std::cout << "Socket fd is in the list of listening sockets.\nWe can accept this client." << std::endl;
				int client_fd = AcceptNewConnection(kev_trigger[i].ident);
				AddToConnectionMap(client_fd);
			}
			else if (kev_trigger[i].filter == EVFILT_READ) {
				if (DEBUG) std::cout << "READ EVENT TRIGGERED" << std::endl;
				recv_msg(kev_trigger[i].ident, kev_trigger[i].data);
			}
			else if (kev_trigger[i].filter == EVFILT_WRITE) {
				if (DEBUG) std::cout << "WRITE EVENT TRIGGERED" << std::endl;
				write_msg(kev_trigger[i].ident);
			}

			if (DEBUG) PrintConnectionMap();
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

	// add the client
	Connection		*new_conn = new Connection(client_fd, _config_file);
	_connection_map.insert(std::make_pair(client_fd, new_conn));

	// this new client now needs to be added to the kqueue
	// so events on this client will also be triggered
	// first we need to prep a kevent struct to note what events we
	// are interested in, then we need to add this event to the kqueue.
	struct kevent	kev_monitor;
	EV_SET(&kev_monitor, client_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL); // add EV_ENABLE or no
	if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
		throw KeventErrorException();
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

// this needs to be changed for dispatch
void KernelEvents::serveHTML(int s, std::string file_path) {
    char htmlresponse[] = "HTTP/1.1 200 OK\r\n"
                    "Connection: close\r\n"
                    "Content-type: text/html\r\n"
                    "\r\n";

	file_path = file_path.substr(9);

	/* 
	**	target part is sketchy, this will be deleted and send to dispatch
	*/ 

	TargetConfig	*target = new TargetConfig();
	target->Setup(_config_file, "localhost", "80", file_path);
	std::string final_path = target->GetResolvedPath();

	if (DEBUG) std::cout << "file path: " << final_path << std::endl;

    std::string		text;
    std::ifstream	read_file(final_path.c_str());

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

/*
**	Receive data sent to the socket fildes, and saves it into buffer
**	The buffer is double checked with the read event data filter
**	As this already knows how much to read.
*/
void KernelEvents::recv_msg(int s, int read_filter_length) {
	std::string	full_request;
	char 		buf[100];
	int			bytes_read;
	int			total_bytes_read = 0;

	while ((bytes_read = recv(s, buf, sizeof(buf) - 1, 0)) > 0) {
		buf[bytes_read] = 0;
		full_request.append(buf);
		total_bytes_read += bytes_read;
	}

	if (total_bytes_read != read_filter_length)
		throw RecvException();

	std::cout << std::endl << "************* START CLIENT REQUEST *************" << std::endl;
	std::cout << full_request << std::endl;
	std::cout << "************* END CLIENT REQUEST *************" << std::endl << std::endl;

	std::map<int, Connection*>::const_iterator it2 = _connection_map.find(s);
	if (it2 != _connection_map.end()) {
		it2->second->Receive(full_request.c_str());
	}

	// register a write event for this event
	struct kevent	kev_monitor;
	EV_SET(&kev_monitor, s, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(_kqueue, &kev_monitor, 1, NULL, 0, NULL) == -1)
		throw KeventErrorException();
}

void	KernelEvents::write_msg(int s) {
	std::map<int, Connection*>::const_iterator it = _connection_map.find(s);
	if (it != _connection_map.end()) {
		// it->second->Dispatch();
		serveHTML(s, it->second->GetRequestPath());
		RemoveFromConnectionMap(s);
		/*
		**	CHECK connection->isDone/ close connection
		*/
	}
}

