#include "connection.hpp"

// Socket fd & config file constructor
Connection::Connection(int fd, NginxConfig* config)
	:	_config(config),
		_request(config),
		_response_handler(),
		_fd(fd),
		_close_connection(false) {}

// Destructor
Connection::~Connection() {}

void	Connection::Receive(char const* buffer) {
	_request.Parse(buffer);

	Request::Status	status = _request.GetRequestStatus();
	switch(status) {
		case Request::Status::Incomplete:
			break;
		case Request::Status::Bad:
			return _response_handler.HandleError(_request);
		case Request::Status::Expect:
			return _response_handler.HandleExpect(_request);
		case Request::Status::Complete:
			return _response_handler.HandleRegular(_request);
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