#include "connection.hpp"

// Socket fd & config file constructor
Connection::Connection(int fd, NginxConfig* config)
	:	_config(config),
		_request(config),
		_response(),
		_fd(fd),
		_close_connection(false) {}

// Destructor
Connection::~Connection() {}

void	Connection::Receive(char const* buffer) {
	_request.Parse(buffer);

	Request::Status	status = _request.GetStatus();
	switch(status) {
		case Request::Status::Incomplete:
			break;
		case Request::Status::Bad:
			_response.HandleError(); break;
		case Request::Status::Complete:
			_response.HandleRegular(); break;
		case Request::Status::Expect:
			_response.HandleExpect(); break;
	}
}

void	Connection::Dispatch() {

}


// void	RequestValidator::ResolveTarget(Request& request) {
// 	(void)request;

// // 	string	target = request.GetTargetURI().GetPath();
// // 	string	resolved_target_path = _target_config->GetResolvedPath(target);
// // 	request.SetResolvedTargetPath(resolved_target_path);
// }