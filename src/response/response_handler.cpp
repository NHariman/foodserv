#include "response_handler.hpp"

// Default constructor
ResponseHandler::ResponseHandler() {
    
}

// Destructor
ResponseHandler::~ResponseHandler() {}

void ResponseHandler::HandleError(Request& request) {
    int	error_code = request.GetStatusCode();
	std::map<int, std::string>	custom_error_pages;
	
	custom_error_pages = request.GetTargetConfig().GetErrorPage();
	// if a custom error page has been specified for that error code
	if (custom_error_pages.find(error_code) != custom_error_pages.end()) {
		
	}
}

void ResponseHandler::HandleExpect(Request& request) {
    
}

void ResponseHandler::HandleRegular(Request& request) {
    
}
