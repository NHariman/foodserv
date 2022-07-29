#ifndef SERVER_HPP
# define SERVER_HPP

#include "socket.hpp"
#include <unistd.h>

class Server {
	private:
		Socket*	_listening_socket;

		char	buffer[4069];
		int		_new_socket;

	public:
		Server(int domain, int port, u_long interface);
		
		void	launch();
		void	accepter();
		void	handler();
		void	responder();

};

#endif