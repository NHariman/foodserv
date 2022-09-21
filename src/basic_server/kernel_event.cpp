#include "kernel_event.hpp"


KernelEvent::KernelEvent(int sock) : _listening_socket(sock) {
    int kq = kqueue();
    struct kevent evSet;
    
    EV_SET(&evSet, _listening_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    kevent(kq, &evSet, 1, NULL, 0, NULL);
    run_event_loop(kq, _listening_socket);
}

void	KernelEvent::run_event_loop(int kq, int _listening_socket) {
    struct kevent evSet;
    struct kevent evList[MAX_EVENTS];
    struct sockaddr_storage addr;
    socklen_t socklen = sizeof(addr);

    while (1) {
        int num_events = kevent(kq, NULL, 0, evList, MAX_EVENTS, NULL);
        for (int i = 0; i < num_events; i++) {
            // receive new connection
            int ident_fd = evList[i].ident;
            if (ident_fd == _listening_socket) {
                int fd = accept(ident_fd, (struct sockaddr *) &addr, &socklen);
                if (addNewClientFd(fd) == 0) {
                    EV_SET(&evSet, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
                    kevent(kq, &evSet, 1, NULL, 0, NULL);
                    serveHTML(fd);
                } else {
                    printf("connection refused.\n");
                    close(fd);
                }
            } // client disconnected
            else if (evList[i].flags & EV_EOF) {
                // int fd = evList[i].ident;
                printf("client #%d disconnected.\n", getClientPos(ident_fd));
                EV_SET(&evSet, ident_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                kevent(kq, &evSet, 1, NULL, 0, NULL);
                deleteClientFd(ident_fd);
            } // read message from client
            else if (evList[i].filter == EVFILT_READ) {
                recv_msg(ident_fd);
                // EV_SET()
            }
        }
    }	
}


void KernelEvent::serveHTML(int s) {
    
    const char *file_path = "../../HTML/index.html";

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

int KernelEvent::getClientPos(int fd) {
    for (int i = 0; i < SOMAXCONN; i++)
        if (clients[i].fd == fd)
            return i;
    return -1;
}

int KernelEvent::addNewClientFd(int fd) {
    if (fd < 1) return -1;
    int i = getClientPos(0);
    if (i == -1) return -1;
    clients[i].fd = fd;
    return 0;
}

int KernelEvent::deleteClientFd(int fd) {
    if (fd < 1) return -1;
    int i = getClientPos(fd);
    if (i == -1) return -1;
    clients[i].fd = 0;
    return close(fd);
}

void KernelEvent::recv_msg(int s) {
    char buf[MAX_MSG_SIZE];
    int bytes_read = recv(s, buf, sizeof(buf) - 1, 0);
    buf[bytes_read] = 0;
    printf("client message #%d:\n %s", getClientPos(s), buf);
    fflush(stdout);
}
