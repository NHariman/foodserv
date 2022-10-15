#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "../config/nginx_config.hpp"
#include "../request/request.hpp"
#include "../response/response_handler.hpp"
#include "../utils/timer.hpp"

class Connection {
	public:
		enum class State {
			Start = 0,
			Request,
			Response,
			CGI,
			Done
		};

		// Socket fd & config file constructor
		Connection(int fd, NginxConfig* config);
		// Destructor
		~Connection();

		void	Receive(char const* buffer);
		void	Dispatch();
		bool	CanClose() const;
		bool	CloseImmediately() const;
		bool	HasTimedOut(double timeout = TIMEOUT_SEC);
		void	HandleTimeout();
		void	SetNextState(Request::Status status);

		// debug
		Response const& DebugGetResponse();

	private:
		Request			_request;
		ResponseHandler	_response_handler;
		int				_socket_fd;
		State			_state;
		bool			_close_connection_immediate;
		Timer			_timer;
};

#endif /* CONNECTION_HPP */
