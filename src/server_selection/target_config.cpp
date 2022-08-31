#include "target_config.hpp"

/*
Variables inside TargetConfig, inherited from LocationContext and ConfigValues

        LocationUri					_location_uri;
		std::string					_cgi_pass;
		AllowedMethods				_allowed_methods;
        std::string					_root;
		std::vector<std::string>	_index;
		size_t						_client_max_body_size;
		std::vector<ErrorPage>		_error_page;
		bool						_autoindex;
		ReturnDir					_return_dir;
*/

void    TargetConfig::SetupTargetConfig(std::string host, std::string port, std::string target, NginxConfig *config) {
    //ServerSelection server(host, port, config);
   // LocationContext location = GetTarget(&server.GetServer(), target);
    ServerContext   server = GetHostServer(host, config); // temp
    LocationContext location = GetTarget(&server, target); // temp

    // only set in location
    _location_uri = location.GetLocationUri();
    _cgi_pass = location.GetCGIPass();
    _allowed_methods = location.GetAllowedMethods();

    // can be set in either location OR server
	_root = SetRoot(&server, &location);
	_index = SetIndex(&server, &location);
	_client_max_body_size = SetMaxBodySize(&server, &location);
	_error_page = SetErrorPage(&server, &location);
	_autoindex = SetAutoindex(&server, &location);
	_return_dir = SetReturn(&server, &location);
}

/// private getters
std::string     TargetConfig::SetRoot(ServerContext *server, LocationContext *location) {
    if (location->IsSet("root"))
        return (location->GetRoot());
    return server->GetRoot();
}

std::vector<std::string>			TargetConfig::SetIndex(ServerContext *server, LocationContext *location) {

	if (location->IsSet("index"))
		return location->GetIndex();
	return server->GetIndex();
}

size_t								TargetConfig::SetMaxBodySize(ServerContext *server, LocationContext *location) {

	if (location->IsSet("client_max_body_size"))
		return location->GetClientMaxBodySize();
	return server->GetClientMaxBodySize();
}

std::vector<ErrorPage>				TargetConfig::SetErrorPage(ServerContext *server, LocationContext *location) {

	if (location->IsSet("error_page"))
		return location->GetErrorPage();
	return server->GetErrorPage();
}

bool								TargetConfig::SetAutoindex(ServerContext *server, LocationContext *location) {

	if (location->IsSet("autoindex"))
		return location->GetAutoindex();
	return server->GetAutoindex();
}

ReturnDir							TargetConfig::SetReturn(ServerContext *server, LocationContext *location) {

	if (location->IsSet("return"))
		return location->GetReturn();
	return server->GetReturn();
}

// public getters
bool							TargetConfig::IsAllowedMethod(std::string method) {

	switch (IsValidHTTPMethod(method)) {
		case GET:
			return _allowed_methods.GetGET();
		case POST:
			return _allowed_methods.GetPOST();
		case DELETE:
			return _allowed_methods.GetDELETE();
	}
	return false;
}

CGIPass						TargetConfig::GetCGIPass() const {
	return _cgi_pass;
}

std::string					TargetConfig::GetRoot() const {
	return _root;
}

std::vector<std::string> 	TargetConfig::GetIndex() const {
	return _index;
}

size_t						TargetConfig::GetMaxBodySize() const {
	return _client_max_body_size;
}

std::vector<ErrorPage>		TargetConfig::GetErrorPage() const {
	return _error_page;
}

bool						TargetConfig::GetAutoindex() const {
	return _autoindex;
}

ReturnDir 					TargetConfig::GetReturn() const {
	return _return_dir;
}

