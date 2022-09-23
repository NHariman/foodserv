#include "target_config.hpp"

/*
Variables inside TargetConfig, inherited from LocationContext and ConfigValues

        LocationUri					_location_uri;
		std::string					_cgi_pass;
		AllowedMethods				_allowed_methods;
        std::string					_root;
		std::string					_alias;
		std::vector<std::string>	_index;
		size_t						_client_max_body_size;
		std::vector<ErrorPage>		_error_page;
		bool						_autoindex;
		ReturnDir					_return_dir;

		// unique
		ServerContext						_server;
		LocationContext						_location;
		std::string							_final_path;	
*/

TargetConfig&	TargetConfig::operator= (TargetConfig const &obj) {
	if (this == &obj)
		return *this;
	_location_uri = obj._location_uri;
	_cgi_pass = obj._cgi_pass;
	_allowed_methods = obj._allowed_methods;
	_root = obj._root;
	_alias = obj._alias;
	_index = obj._index;
	_client_max_body_size = obj._client_max_body_size;
	_error_page = obj._error_page;
	_autoindex = obj._autoindex;
	_return_dir = obj._return_dir;

	_server = obj._server;
	_location = obj._location;
	_resolved_path = obj._resolved_path;
	return (*this);
}

void    TargetConfig::Setup(NginxConfig *config, std::string host, std::string port, std::string target) {
    ServerSelection server(host, port, config->GetServers());
	_server = server.GetChosenServerContext();

	
	LocationSelection	location(_server, target);
    _location = location.GetLocationContext();

    // only set in location
    _location_uri = _location.GetLocationUri();
	_cgi_pass = _location.GetCGIPass();
    _allowed_methods = _location.GetAllowedMethods();
	_alias = _location.GetAlias();

    // can be set in either location OR server
	_root = SetRoot(&_server, &_location);
	_index = SetIndex(&_server, &_location);
	_client_max_body_size = SetMaxBodySize(&_server, &_location);
	_error_page = SetErrorPage(&_server, &_location);
	_autoindex = SetAutoindex(&_server, &_location);
	_return_dir = SetReturn(&_server, &_location);

	ResolvedPath	resolved_path(this, target);
	_resolved_path = resolved_path.GetResolvedPath();
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

std::map<int, std::string>				TargetConfig::SetErrorPage(ServerContext *server, LocationContext *location) {

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

void		TargetConfig::SetGenerateIndexBool(bool index) {
	_generate_index = index;
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

std::vector<std::string>	TargetConfig::GetAllowedMethods() const {
	return _allowed_methods.GetMethods();
}

size_t						TargetConfig::GetMaxBodySize() const {
	return _client_max_body_size;
}

std::string			TargetConfig::GetResolvedPath() const {
	return _resolved_path;
}

ServerContext		TargetConfig::GetServer() const {
	return _server;
}

LocationContext		TargetConfig::GetLocation() const {
	return _location;
}

bool				TargetConfig::MustGenerateIndex() const {
	return _generate_index;
}	
