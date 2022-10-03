#ifndef CONNECTION_TEST_HPP
#define CONNECTION_TEST_HPP

#include "../config/nginx_config.hpp"
#include "../request/request.hpp"
#include "../response/response_handler.hpp"
// #include "response.hpp"

class Connection {
	public:
		// Socket fd & config file constructor
		Connection(int fd, NginxConfig* config);
		// Destructor
		~Connection();

		void	Receive(char const* buffer);
		void	Dispatch();
		// debug
		Response const& DebugGetResponse();

        /* EXTRA SANNE */ std::string GetRequestPath();

	private:
		NginxConfig*	_config;
		Request			_request;
		ResponseHandler	_response_handler;
		int				_fd; // TODO: change to specific socket/connection_fd
		bool			_close_connection;

        /* EXTRA SANNE */   std::string _request_path;
};

#endif /* CONNECTION_HPP */
