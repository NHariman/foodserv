#include "response_handler.hpp"
#include "response_generator.hpp"
#include "../cgi/cgi_handler.hpp"
#include "../utils/config_utils.hpp"
#include <algorithm>
#include <sys/socket.h> // send

#define DEBUG 0 // TODO: REMOVE

// Default constructor
ResponseHandler::ResponseHandler()
		:	_request(NULL), _is_done(false) {
	_response = Response::pointer(new Response);
}

// Destructor
ResponseHandler::~ResponseHandler() {}

bool	ResponseHandler::Ready() {
	return _response->IsComplete();
}

bool	ResponseHandler::IsDone() const {
	return _is_done;
}

void	ResponseHandler::Send(int fd) {
	std::istream*	to_send = _response->GetCompleteResponse();
	char	buffer[BUFFER_SIZE];

	if (DEBUG) std::cout << "ResponseHandler:Send:\n[[" << to_send->rdbuf() << "]]\n";
	
	size_t send_size = std::min((size_t)BUFFER_SIZE, GetStreamSize(to_send));
	if (DEBUG) std::cout << "send size is " << send_size << std::endl;
	if (send_size != 0) {
		to_send->read(buffer, send_size);
		buffer[send_size] = '\0'; // stream::read doesn't append null terminator

		if (DEBUG) std::cout << "stream good: " << to_send->good() << " | eof: " << to_send->eof() << std::endl;
		if (DEBUG) std::cout << "Bytes read: " << to_send->gcount() << std::endl;

		// save send return to check for error or less bytes sent than indicated
		ssize_t bytes_sent = send(fd, buffer, send_size, 0);

		if (bytes_sent < 0) {
			// throw SendFailureException();
			std::cout << "send failed: " << strerror(errno) << "\n"; // remove
		}
		if (DEBUG) std::cout << "bytes sent: " << bytes_sent << std::endl;

		// shift position of next character to extract
		to_send->seekg(std::min(send_size, (size_t)bytes_sent));
	}

	// if an Expect request was processed, a 2nd final response still has to be
	// served once the message body is received.
	if (_response->GetStatusCode() == 100)
		_response = Response::pointer(new Response); // create fresh Response object
	// if no more bytes to send, close connection
	else if (send_size == 0)
		_is_done = true;
}

void	ResponseHandler::HandleError(Request& request) {
	if (DEBUG) std::cout << "HandleError\n";

	_request = &request;
	int	error_code = request.GetStatusCode();
	
	std::string	custom_error_page = FindCustomErrorPage(error_code);
	if (!custom_error_page.empty())
		return HandleCustomError(custom_error_page);
	else
		return HandleDefaultError(error_code);
}

void	ResponseHandler::HandleExpect(Request& request) {
	_request = &request;

	if (DEBUG) std::cout << "HandleExpect\n";
	FormResponse();
}

void	ResponseHandler::HandleRegular(Request& request) {
	if (DEBUG) std::cout << "HandleRegular\n";

	_request = &request;

	if (IsRedirected())
		return HandleRedirection();
	try {
		AssignResponseResolvedPath();
		// check cgi
		if (IsHandledByCGI())
			HandleCGI();
		else
			HandleMethod();
		FormResponse();
	}
	catch (http::exception &e) {
		_request->SetStatusCode(e.which());
		HandleError(*_request);
	}
}

Response const&	ResponseHandler::GetResponse() {
	return *_response;
}

// Checks if request target path was able to be resolved.
// If so, assigns response path. If not, throws a 404: Not Found.
// Takes optional path argument for different path than request::resolved_path.
void	ResponseHandler::AssignResponseResolvedPath(std::string const& path) {
	std::string resolved_path;

	if (path.empty())
		resolved_path = _request->GetTargetConfig().GetResolvedPath();
	else
		resolved_path = path;

	if (resolved_path.empty())
		throw NotFoundException();
	else if (IsDirectory(resolved_path) && !IsValidDirectory(resolved_path))
		throw ForbiddenException();
	else
		_response->SetResolvedPath(resolved_path);
	_response->SetRequestTarget(_request->GetTargetString());
	if (DEBUG) std::cout << "path assigned to: " << _response->GetResolvedPath() << std::endl;
}

std::string	ResponseHandler::FindCustomErrorPage(int error_code) {
	std::map<int, std::string>	custom_error_pages;
	
	custom_error_pages = _request->GetTargetConfig().GetErrorPage();
	auto custom_page = custom_error_pages.find(error_code);
	// if a custom error page has been specified for that error code
	if (custom_page != custom_error_pages.end())
		return custom_page->second;
	return "";
}

void	ResponseHandler::HandleCustomError(std::string const& error_page_path) {
	std::string root = _request->GetTargetConfig().GetRoot();
	std::string resolved_error_path = root + error_page_path;

	try {
		AssignResponseResolvedPath(resolved_error_path);
		HandleMethod();
		FormResponse();
	}
	catch (http::exception &e) {
		_request->SetStatusCode(e.which());
		if (DEBUG) std::cout << e.which() << " error encountered\n";
		HandleError(*_request);
	}
}

void	ResponseHandler::HandleDefaultError(int error_code) {
	std::string error_page_html(GetServerErrorPage(error_code));
	std::istream* body_stream = CreateStreamFromString(error_page_html);

	_response->SetBodyStream(body_stream);
	_response->SetHeaderField("Content-Type", "text/html");
	FormResponse();
}

bool	ResponseHandler::IsRedirected() {
	ReturnDir return_dir = _request->GetTargetConfig().GetReturn();

	if (return_dir.IsSet()) {
		_response->SetStatusCode(return_dir.GetCode());
		return true;
	}
	return false;
}

void	ResponseHandler::HandleRedirection() {
	_response->SetResolvedPath(_request->GetTargetConfig().GetResolvedPath());
	FormResponse();
}

bool	ResponseHandler::IsHandledByCGI() {
	return _request->GetTargetConfig().GetCGIPass().IsSet();
}

void	ResponseHandler::HandleCGI() {
	CGIHandler	cgi_handler;
	std::istream* body_stream = cgi_handler.Execute(_request, *_response);
<<<<<<< HEAD
	_response->SetBodyStream(body_stream);
=======
>>>>>>> Moved Response forming functions out of ResponseHandler and into ResponseGenerator
}

// Assumes _response->_resolved_path has been set already.
void	ResponseHandler::HandleMethod() {
	FileHandler::Method method = DetermineMethod();
	std::istream* body_stream = _file_handler.ExecuteMethod(*_response, method);
	_response->SetBodyStream(body_stream);
}

FileHandler::Method ResponseHandler::DetermineMethod() {
	if (_request->GetStatusCode() > 399) // error status
		return FileHandler::Method::GetError;
	else if (_request->GetTargetConfig().MustGenerateIndex() == true) {
		return FileHandler::Method::GetGeneratedIndex;
	}
	else {
		std::string method = _request->GetMethod();
		if (method == "GET")
			return FileHandler::Method::Get;
		else if (method == "POST") {
			_response->SetMessageBody(_request->GetMessageBody());
			return FileHandler::Method::Post;
		}
		else if (method == "DELETE")
			return FileHandler::Method::Delete;
		else
			throw InternalServerErrorException();
	}
}

void	ResponseHandler::FormResponse() {
	ResponseGenerator	response_generator;

	response_generator.FormResponse(*_response, _request);
	if (DEBUG) std::cout << "Response formed. Final status code: " << _response->GetStatusCode() << std::endl;
}

#undef DEBUG // REMOVE
