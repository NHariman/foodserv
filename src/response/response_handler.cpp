#include "response_handler.hpp"
#include "../utils/config_utils.hpp"

#define DEBUG 0 // TODO: REMOVE

// Default constructor
ResponseHandler::ResponseHandler()
		:	_request(NULL), _is_done(false) {
	_response = ResponsePtr(new Response);
}

// Destructor
ResponseHandler::~ResponseHandler() {}

bool	ResponseHandler::Ready() {
	return _response->IsComplete();
}

void	ResponseHandler::Send() {
	std::istream*	to_send = _response->GetCompleteResponse();

	// if (DEBUG) std::cout << "ResponseHandler:Send:\n" << to_send->rdbuf() << std::endl;

	// if an Expect request was processed, a 2nd final response still has to be
	// served once the message body is received.
	if (_response->GetStatusCode() == 100)
		_response = ResponsePtr(new Response); // create fresh Response object
	else
		_is_done = true;
}

bool	ResponseHandler::IsDone() const {
	return _is_done;
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
	SetStatusLine();
	if (_response->GetStatusCode() != 100)
		SetHeaders();
	_response->SetComplete();

	if (DEBUG) std::cout << "Response formed. Final status code: " << _response->GetStatusCode() << std::endl;
}

void	ResponseHandler::SetStatusLine() {
	_response->SetHTTPVersion("HTTP/1.1");
	if (_response->GetStatusCode() == 0)
		_response->SetStatusCode(_request->GetStatusCode());
	_response->SetReasonPhrase(GetReasonPhrase(_response->GetStatusCode()));
}

void	ResponseHandler::SetHeaders() {
	SetAllow();
	SetConnection();
	SetContentLength();
	SetContentType();
	SetDate();
	SetLocation();
	SetServer();
}

// Allow is only set if returning a 405: Method Not Allowed error.
void	ResponseHandler::SetAllow() {
	if (_response->GetStatusCode() == 405)
		_response->SetHeaderField("Allow", GetAllowedMethodsString());
}

// Connection: close is always sent unless it's a 100: Continue response.
void	ResponseHandler::SetConnection() {
	_response->SetHeaderField("Connection", "close");
}

void	ResponseHandler::SetContentLength() {
	std::istream* body_stream = _response->GetBodyStream();
	if (body_stream != NULL
			&& _response->GetField("Content-Length") == NO_VAL) {
		body_stream->seekg(0, std::ios_base::end); // move cursor to end of stream
		std::streampos	size = body_stream->tellg(); // get position of cursor
		_response->SetHeaderField("Content-Length", std::to_string(size));
		body_stream->seekg(0); // restore cursor to beginning
	}
}

void	ResponseHandler::SetContentType() {
	// check if there is payload & type not already set
	if (_response->GetBodyStream() != NULL
			&& _response->GetField("Content-Type") == NO_VAL) {
		size_t	extension_start = _response->GetResolvedPath().find_last_of(".");
		std::string	type;

		type = GetType(_response->GetResolvedPath().substr(extension_start + 1));
		if (type.empty()) // if no extension or unknown extension
			type = "application/octet-stream";
		_response->SetHeaderField("Content-Type", type);
	}
}

void	ResponseHandler::SetDate() {
	char	buf[100];
	time_t	now = time(0);
	struct tm	tm = *gmtime(&now);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %Z", &tm);

	_response->SetHeaderField("Date", std::string(buf));
}

// Location only set if request is redirected or a POST request is successfully executed (201 created).
void	ResponseHandler::SetLocation() {
	int status_code = _response->GetStatusCode();
	if (IsRedirectCode(status_code))
		_response->SetHeaderField("Location", _response->GetResolvedPath());
	else if (status_code == 201)
		_response->SetHeaderField("Location", _request->GetTargetString());
}

void	ResponseHandler::SetServer() {
	_response->SetHeaderField("Server", "foodserv/1.0");
}

// Used by SetAllow to set header value to comma-separated list of allowed methods.
std::string	ResponseHandler::GetAllowedMethodsString() {
	std::vector<std::string> methods_vec = _request->GetTargetConfig().GetAllowedMethods();
	std::string	methods_str;

	for (auto it = methods_vec.begin(); it != methods_vec.end(); it++) {
		if (!methods_str.empty())
			methods_str += ", ";
		methods_str += *it;
	}
	return methods_str;
}

#undef DEBUG // REMOVE
