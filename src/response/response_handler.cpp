#include "response_handler.hpp"
#include "file_handler.hpp"

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
}

void ResponseHandler::HandleExpect(Request& request) {
	_request = &request;
}

void ResponseHandler::HandleRegular(Request& request) {
	_request = &request;
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

	std::string	resolved_error_page_path = error_target_config.GetResolvedPath();
	try {
		std::string error_page_content = _file_h.GetFileContents(resolved_error_page_path);
		_response.SetMessageBody(error_page_content);
	}
	catch (http::exception &e) {
		_request->SetStatusCode(e.which());
		HandleError(*_request);
	}
}



// void	RequestValidator::ResolveTarget(Request& request) {
// 	(void)request;

// // 	string	target = request.GetTargetURI().GetPath();
// // 	string	resolved_target_path = _target_config->GetResolvedPath(target);
// // 	request.SetResolvedTargetPath(resolved_target_path);
// }

