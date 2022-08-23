#include "KernelEvent.hpp"

KernelEvent::KernelEvent() : _ListenSocketClass("::", "12345") {
    _listening_socket = _ListenSocketClass.getListeningSocket();
    // initializing kqueue
    initKqueue();
    // installing reading socket event set
    createEventSetMonitor();
    
    // changes to events to triggers and event_list
    struct kevent eventToSet;
    struct kevent eventList[SOMAXCONN];

    // int _addrlen = _ListenSocketClass.getAddrLen();
    // struct addrinfo* _addrinfo = _ListenSocketClass.getAddrInfo();

    // keventLoop();

    // in this event loop kevent will be called to receive incoming events and process them
    while (1) {
        // std::cout << "in start of while" << std::endl;
        int num_events = kevent(_kq, NULL, 0, eventList, SOMAXCONN, NULL);
        std::cout << "Number of events: " << num_events << std::endl;
        
        if (num_events < 0) {
            perror("kevent");
            exit (EXIT_FAILURE);
        }


        // std::cout << "Number of events happening: " << num_events << std::endl;
        // eventList is the structure that holds all events currently kept track of .filter shows which event this is

        for (int i = 0; i < num_events; i++) {
            // if (evList[i].flags & EV_EOF) {}
            // check if the connection is equal to the listening socket
            // if this is the case we know a client is sending a request to us.
            if (eventList[i].ident == _listening_socket) {
                int fd_to_accept = accept(eventList[i].ident, (struct sockaddr*)&_addrinfo, (socklen_t*)&_addrlen);
                std::cout << "value of fd_to_accept: " << fd_to_accept << std::endl;
                
                // THIS IS THE HTTP REQUEST OF THE NEWLY ACCEPTED CLIENT
                // NOW WE NEED TO PROCESS THIS REQUEST. 
                // THIS IS THE PART WHERE I HAVE TO ADD IN MICHELLES CODE

                // function: receive request
                std::cout << "amount of data ready to read in the event  -> backlog: " << eventList[i].data << std::endl;
                
                char HTTPREQUEST[1000];
                memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
                std::cout << "Amount read by recv: " << recv(fd_to_accept, HTTPREQUEST, sizeof(HTTPREQUEST), 0) << std::endl;
                std::cout << HTTPREQUEST << std::endl;
                // HOW DO WE PRINT THE REQUEST A CLIENT IS SENDING?

                // we now have a connection that we have accepted
                // the fd should be added in our list of events: eventlist
                if (addClientFd(fd_to_accept) < 0) {
                    std::cout << "Connection " << fd_to_accept << " can not be added." << std::endl;
                    close(fd_to_accept);
                    // close(_listening_socket);
                    // exit( EXIT_FAILURE) ;
                }
                else {
                    EV_SET(&eventToSet, fd_to_accept, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR, 0, SOMAXCONN, NULL);
                    kevent(_kq, &eventToSet, 1, NULL, 0, NULL);
                    // ADD IN: send the correct html to the client
                    // this is where we send a message to the client
                    // this should be depended on what the clients requests, but for now we will
                    // send a basic HTML message
                    send(fd_to_accept, html, sizeof(html), 0);
                }

            }
            // check is the connection is disconnected
            else if (eventList[i].flags & EV_EOF) {
                std::cout << "Client disconnected: " << eventList[i].ident << std::endl;
                EV_SET(&eventToSet, eventList[i].ident, EVFILT_READ, EV_DELETE | EV_DISABLE, 0, 0, NULL);
                kevent(_kq, &eventToSet, 1, NULL, 0, NULL);
                deleteLostConnections(eventList[i].ident);
            }

            //  if (eventList[i].filter == EVFILT_READ && i == 1)
            //     std::cout << "READY TO READ SOMETHING ON FILDES (hopefully _listening_socket?): " << eventList[i].ident << std::endl;
            //     // break ;

            else if (eventList[i].filter == EVFILT_READ) {
                // never happens yet
                // guessing this is when you have a link within a website
                std::cout << "in the evfilt_read" << std::endl;
                char buf[1000];
                int bytes_read = recv(eventList[i].ident, buf, sizeof(buf) - 1, 0);
                buf[bytes_read] = 0;
                printf("client #%d: %s", findClientFd(eventList[i].ident), buf);
                // fflush(stdout);
            }


        }
    }
}

void    KernelEvent::initKqueue() {
    _kq = kqueue();
    if (_kq == -1) {
        perror("kqueue");
        exit (EXIT_FAILURE);
    }
}

int     KernelEvent::findClientFd(int fd) {
    for (int i = 0; i < SOMAXCONN; i++) {
        if (_clients[i].fd == fd)
            return i; // dit was return 1, check this
    }
    // return -1 is no matching FD is found
    return -1;
}

// for a new connection (request) add in the fd in the _clients array
// the place to store is is the first fd == 0
int	    KernelEvent::addClientFd(int fd) {
    // return -1 on an invalid fd
    if (fd < 1)
        return -1;
    int	i;
    // looks for the position of the first empty spot
    i = findClientFd(0);
    if (i == -1)
        return -1;
    _clients[i].fd = fd;
    return 0;
}

// when a connection is lost, we dont want that client_fd to stay
// in the array of _clients fd's
int	    KernelEvent::deleteLostConnections(int fd) {
    if (fd < 1)
        return -1;
    int i;
    // find position in the array where to delete
    i = findClientFd(fd);
    if (i == -1)
        return -1;
    _clients[i].fd = 0;
    if (close(fd) == -1)
        return -1;
    return 0;
}