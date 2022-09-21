#include "response_handler.hpp"

// Config file constructor
ResponseHandler::ResponseHandler(NginxConfig* config)
	:	_config(config), _request(NULL) {}

// Destructor
ResponseHandler::~ResponseHandler() {}

void ResponseHandler::HandleError(Request& request) {
	_request = &request;
	int	error_code = request.GetStatusCode();
	
	std::string	custom_error_page = FindCustomErrorPage(error_code);
	if (!custom_error_page.empty())
		return HandleCustomError(custom_error_page);
	// else
	// 	return HandleDefaultError
}

void ResponseHandler::HandleExpect(Request& request) {
	_request = &request;
}

void ResponseHandler::HandleRegular(Request& request) {
	_request = &request;

	_response.SetResolvedPath(_request->GetTargetConfig().GetResolvedPath());
	if (IsRedirected())
		return BuildResponse();
	// check cgi
	// filehandler executor
}

bool	ResponseHandler::IsRedirected() {
	ReturnDir return_dir = _request->GetTargetConfig().GetReturn();

	if (return_dir.IsSet()) {
		_request->SetStatusCode(return_dir.GetCode());
		return true;
	}
	return false;
}

std::string ResponseHandler::FindCustomErrorPage(int error_code) {
	std::map<int, std::string>	custom_error_pages;
	
	custom_error_pages = _request->GetTargetConfig().GetErrorPage();
	auto custom_page = custom_error_pages.find(error_code);
	// if a custom error page has been specified for that error code
	if (custom_page != custom_error_pages.end())
		return custom_page->second;
	return "";
}

void ResponseHandler::HandleCustomError(std::string const& error_page_path) {
	std::string	host = _request->GetTargetURI().GetHost();
	std::string	port = _request->GetTargetURI().GetPort();

	TargetConfig	error_target_config;
	error_target_config.Setup(_config, host, port, error_page_path);

	_response.SetResolvedPath(error_target_config.GetResolvedPath());
	try {
		std::ifstream* file = _file_handler.GetFile(_response.GetResolvedPath());
		_response.SetFileStream(file);
	}
	catch (http::exception &e) {
		_request->SetStatusCode(e.which());
		HandleError(*_request);
	}
}

void	ResponseHandler::BuildResponse() {
    SetStatusLine();
	SetHeaders();
	// setfilestream for message body?
}


void	ResponseHandler::SetStatusLine() {
	_response.SetHTTPVersion("HTTP/1.1");
	_response.SetStatusCode(_request->GetStatusCode());
	_response.SetReasonPhrase(GetReasonPhrase(_response.GetStatusCode()));
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
	if (_request->GetStatusCode() == 405)
		_response.SetHeaderField("Allow", GetAllowedMethodsString());
}

// Connection: close is always sent unless it's a 100: Continue response.
void	ResponseHandler::SetConnection() {
	if (_request->GetStatusCode() != 100)
		_response.SetHeaderField("Connection", "close");
}

void	ResponseHandler::SetContentLength() {
	std::istream* file_stream = _response.GetFileStream();
	if (file_stream != NULL) {
		file_stream->seekg(0, std::ios_base::end); // move cursor to end of stream
		streampos	size = file_stream->tellg(); // get position of cursor
		_response.SetHeaderField("Content-Length", std::to_string(size));
		file_stream->seekg(0); // restore cursor to beginning
	}
}

void	ResponseHandler::SetContentType() {
	size_t	extension_start = _response.GetResolvedPath().find_last_of(".");
	std::string	type;

	type = GetType(_response.GetResolvedPath().substr(extension_start + 1));
	if (type.empty()) // if no extension or unknown extension
		type = "application/octet-stream";

	_response.SetHeaderField("Content-Type", type);
}

void ResponseHandler::SetDate() {
	char	buf[1000];
	time_t	now = time(0);
	struct tm	tm = *gmtime(&now);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S %Z", &tm);

	_response.SetHeaderField("Date", std::string(buf));
}

// Location only set if request is redirected or a POST request is successfully executed (201 created).
void	ResponseHandler::SetLocation() {
	int status_code = _request->GetStatusCode();
	if (IsRedirectCode(status_code) || status_code == 201)
		_response.SetHeaderField("Location", _response.GetResolvedPath());
}

void	ResponseHandler::SetServer() {
	_response.SetHeaderField("Server", "foodserv/1.0");
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


// void	ResponseHandler::ResolveTarget() {
// 	string	target = _request->GetTargetURI().GetPath();
// 	string	resolved_path = _request->GetTargetConfig().GetResolvedPath(target);
// 	response.SetResolvedTargetPath(resolved_target_path);
// }

