#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../config/nginx_config.hpp"
#include "../request/request.hpp"
#include "../response/response_handler.hpp"
#include "../utils/timer.hpp"

class Connection {
	public:
		// Socket fd & config file constructor
		Connection(int fd, NginxConfig* config);
		// Destructor
		~Connection();

		void	Receive(char const* buffer);
		void	Dispatch();
		bool	CanClose() const;
		bool	HasTimedOut() const;
		// debug
		Response const& DebugGetResponse();

	private:
		NginxConfig*	_config;
		Request			_request;
		ResponseHandler	_response_handler;
		int				_fd; // TODO: change to specific socket/connection_fd
		bool			_close_connection;
		Timer			_timer;
};

#endif /* CONNECTION_HPP */
