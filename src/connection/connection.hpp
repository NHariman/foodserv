#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "nginx_config.hpp"
#include "request.hpp"

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
		Response		_response;
		int				_fd; // TODO: change to specific socket/connection_fd
		bool			_close_connection;

		void	HandleError();
		void	HandleExpect();
		void	HandleResponse();
};

#endif /* CONNECTION_HPP */
