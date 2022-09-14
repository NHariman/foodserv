#include "connection.hpp"

// Socket fd & config file constructor
Connection::Connection(int fd, NginxConfig* config)
	: _config(config), _request(config), _fd(fd), _close_connection(false) {}

// Destructor
Connection::~Connection() {}

void	Connection::Receive(char const* buffer) {
	_request.Parse(buffer);

	Request::Status	status = _request.GetStatus();
	switch(status) {
		case Request::Status::Incomplete:
			break;
		case Request::Status::Bad:
			HandleError(); break;
		case Request::Status::Complete:
			HandleResponse(); break;
		case Request::Status::Expect:
			HandleExpect(); break;
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