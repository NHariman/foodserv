#include "connection.hpp"

// Socket fd & config file constructor
Connection::Connection(int fd, NginxConfig* config)
	:	_config(config),
		_request(config),
		_response_handler(),
		_fd(fd),
		_close_connection(false) {}

// Destructor
Connection::~Connection() {
}

void	Connection::Receive(char const* buffer) {
	_timer.Reset();

	_request.Parse(buffer);

	Request::Status	status = _request.GetRequestStatus();
	// std::cout << "Connection::Receive: request status_code: " << _request.GetStatusCode() << std::endl;
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
	_timer.Reset();
	
	if (_response_handler.Ready())
		_response_handler.Send(_fd); // can throw, should be caught in main

	if (_response_handler.IsDone())
		_close_connection = true;
}

Response const& Connection::DebugGetResponse() {
	return	_response_handler.GetResponse();
}

bool	Connection::CanClose() const {
	return _close_connection;
}

// Takes optional parameter `timeout` for testing.
// Defaults to TIMEOUT_SEC macro set in utils.hpp.
bool	Connection::HasTimedOut(double timeout) const {
	return _timer.GetElapsed() > timeout;
}
