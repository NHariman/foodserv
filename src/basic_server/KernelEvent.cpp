#include "KernelEvent.hpp"

KernelEvent::KernelEvent() : _ListenSocketClass("::", "12345") {
    // init class listening socket
    // _ListenSocketClass = new ListeningSocket("::", "12345");
    _listening_socket = _ListenSocketClass.getListeningSocket();

    _kq = kqueue();
    std::cout << "Value of _listening_socket: " << _listening_socket << std::endl;
    std::cout << "Value of _kq: " << _kq << std::endl;

    // initialize 2 kevent structs one for read and one for write
    // (sock_fd, EVFILT_READ) pair and  (sock_fd, EVFILT_WRITE) pair.

    // installing reading socket
    struct  kevent changelist;

    // bzero(&ke_read, sizeof(ke_read));

    // use EV_SET to fill the kevent structure
    // set the ident to the _listening_socket
    // changelist.ident = _listening_socket;
    // and the flag to EV_ADD as you want to add it to the kqueue
    // changelist.flag = EV_ADD;
    // set filter on EVFILT_READ as you only want to add when read is possible
    // changelist.filter = EVFILT_READ;
    EV_SET(&changelist, _listening_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);

    // now initialize the kevent() this registers event with the queue and returns any pending events to the user.
    // int kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, int nevents, const struct timespec *timeout);
    kevent(_kq, &changelist, 1, NULL, 0, NULL);

    struct kevent eventToSet;
    struct kevent eventList[SOMAXCONN];
    
    int _addrlen = _ListenSocketClass.getAddrLen();
    struct addrinfo* _addrinfo = _ListenSocketClass.getAddrInfo();

    // in this event loop kevent will be called to receive incoming events and process them
    while (1) {
        // std::cout << "in start of while" << std::endl;
        int num_events = kevent(_kq, NULL, 0, eventList, 1, NULL);
        if (num_events < 0) {
            perror("kevent");
            exit (EXIT_FAILURE);
        }

        // std::cout << "Number of events happening: " << num_events << std::endl;
        // eventList is the structure that holds all events currently kept track of .filter shows which event this is

        for (int i = 0; i < num_events; i++) {
            
            // check if the connection is equal to the listening socket
            // if this is the case we know a client is sending a request to us.
            if (eventList[i].ident == _listening_socket) {
                int fd_to_accept = accept(eventList[i].ident, (struct sockaddr*)&_addrinfo, (socklen_t*)&_addrlen);
                std::cout << "value of fd_to_accept: " << fd_to_accept << std::endl;
                
                // THIS IS THE HTTP REQUEST OF THE NEWLY ACCEPTED CLIENT
                // NOW WE NEED TO PROCESS THIS REQUEST. 
                // THIS IS THE PART WHERE I HAVE TO ADD IN MICHELLES CODE

                // function: receive request

                char HTTPREQUEST[1000];
                memset(HTTPREQUEST, 0, sizeof(HTTPREQUEST));
                recv(fd_to_accept, HTTPREQUEST, sizeof(HTTPREQUEST), 0);
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
                    EV_SET(&eventToSet, fd_to_accept, EVFILT_READ, EV_ADD, 0, 0, NULL);
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
                EV_SET(&eventToSet, eventList[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
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
        // break ;
    }
}

