#include "connection.hpp"

// Socket fd & config file constructor
Connection::Connection(int fd, NginxConfig* config)
	:	_request(config),
		_response_handler(),
		_socket_fd(fd),
		_state(State::Start),
		_close_connection_immediate(false) {}

// Destructor
Connection::~Connection() {
}

void	Connection::Receive(char const* buffer) {
	_state = State::Request;
	
	_timer.Reset();

	_request.Parse(buffer);

	Request::Status	status = _request.GetRequestStatus();
	SetNextState(status);
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
	if (_response_handler.Ready()) {
		_timer.Reset();
		_response_handler.Send(_socket_fd);
	}

	if (_response_handler.IsDone())
		_state = State::Done;
}

Response const& Connection::DebugGetResponse() {
	return	_response_handler.GetResponse();
}

bool	Connection::CanClose() const {
	return _state == State::Done;
}

bool	Connection::CloseImmediately() const {
	return _close_connection_immediate;
}

// Takes optional parameter `timeout` for testing.
// Defaults to TIMEOUT_SEC macro set in utils.hpp.
bool	Connection::HasTimedOut(double timeout) {
	if (_timer.GetElapsed() > timeout) {
		HandleTimeout();
		return true;
	}
	return false;
}

void	Connection::HandleTimeout() {
	if (_state == State::Start) {
		_close_connection_immediate = true;
		return ;
	}
	if (_state == State::CGI)
		_request.SetStatusCode(504);
	else
		_request.SetStatusCode(408);
	_response_handler.HandleError(_request);
}

// Changes internal State as needed for handling timeouts later.
void	Connection::SetNextState(Request::Status status) {
    if (status == Request::Status::Incomplete)
		return;
	else if (_request.GetTargetConfig().GetCGIPass().IsSet()) // CGI
		_state = State::CGI;
	else
		_state = State::Response;
}
