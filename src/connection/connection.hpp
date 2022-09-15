#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "nginx_config.hpp"
#include "request.hpp"
// #include "response.hpp"
#include "response_handler.hpp"

class Connection {
	public:
		// Socket fd & config file constructor
		Connection(int fd, NginxConfig* config);
		// Destructor
		~Connection();

		void	Receive(char const* buffer);
		void	Dispatch();

	private:
		NginxConfig*	_config;
		Request			_request;
		ResponseHandler	_response_handler;
		int				_fd; // TODO: change to specific socket/connection_fd
		bool			_close_connection;
};

#endif /* CONNECTION_HPP */
