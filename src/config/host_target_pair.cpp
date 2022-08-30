#include "nginx_config.hpp"

host_target_pair			NginxConfig::GetHostTargetServer(std::string host, std::string target) const {

	host_target_pair	 host_target_pair;

	for (size_t server = 0 ; server < _servers.size(); server++) {
		for(size_t names = 0 ; names < _servers.at(server).GetServerNameVector().at(names).size() ; names++) {
			if (host.compare(_servers.at(server).GetServerNameVector().at(names)) == 0) {
				host_target_pair.server = _servers.at(server);
				for (size_t loc = 0 ; loc < _servers.at(server).GetLocationContexts().size() ; loc++) {
					if (target.compare(_servers.at(server).GetLocationContexts().at(loc).GetLocationUri().GetUri()) == 0) {
						host_target_pair.location = _servers.at(server).GetLocationContexts().at(loc);
						return (host_target_pair);
					}
				}
			}
		}
	}
	throw HostTargetPairDoesNotExistException(host, target);
	return (host_target_pair);
}

ServerContext			NginxConfig::GetHostServer(std::string host) const {

	for (size_t server = 0 ; server < _servers.size(); server++) {
		for(size_t names = 0 ; names < _servers.at(server).GetServerNameVector().at(names).size() ; names++) {
			if (host.compare(_servers.at(server).GetServerNameVector().at(names)) == 0) {
				return _servers.at(server);
			}
		}
	}
	throw HostDoesNotExistException(host);
}

bool								NginxConfig::IsSetInTarget(std::string host, std::string target, std::string directive) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	return host_target_pair.location.IsSet(directive);
}

bool								NginxConfig::IsSetInHost(std::string host, std::string directive) const {
	ServerContext	 host_serv(GetHostServer(host));
	return host_serv.IsSet(directive);
}

std::string							NginxConfig::GetRoot(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("root"))
		return host_target_pair.location.GetRoot();
	return host_target_pair.server.GetRoot();
}

std::vector<std::string>			NginxConfig::GetIndex(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("index"))
		return host_target_pair.location.GetIndex();
	return host_target_pair.server.GetIndex();
}

size_t								NginxConfig::GetMaxBodySize(std::string host, std::string target) const {

	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("client_max_body_size"))
		return host_target_pair.location.GetClientMaxBodySize();
	return host_target_pair.server.GetClientMaxBodySize();
}

std::vector<ErrorPage>				NginxConfig::GetErrorPage(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("error_page"))
		return host_target_pair.location.GetErrorPage();
	else if (host_target_pair.server.IsSet("error_page"))
		return host_target_pair.server.GetErrorPage();
	throw ConfigValues::DirectiveNotSetException("error_page", host, target);
}

bool								NginxConfig::GetAutoindex(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("autoindex"))
		return host_target_pair.location.GetAutoindex();
	return host_target_pair.server.GetAutoindex();
}

ReturnDir							NginxConfig::GetReturn(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("return"))
		return host_target_pair.location.GetReturn();
	else if (host_target_pair.server.IsSet("return"))
		return host_target_pair.server.GetReturn();
	throw ConfigValues::DirectiveNotSetException("return", host, target);
}

bool							NginxConfig::IsAllowedMethod(std::string host, std::string target, std::string method) const {
	host_target_pair	host_target_pair = GetHostTargetServer(host, target);

	switch (IsValidHTTPMethod(method)) {
		case GET:
			return host_target_pair.location.GetAllowedMethods().GetGET();
		case POST:
			return host_target_pair.location.GetAllowedMethods().GetPOST();
		case DELETE:
			return host_target_pair.location.GetAllowedMethods().GetDELETE();
	}
	return false;
}

std::string					NginxConfig::GetFastCGIPass(std::string host, std::string target) const {
	host_target_pair	 host_target_pair = GetHostTargetServer(host, target);
	if (host_target_pair.location.IsSet("fastcgi_pass"))
		return host_target_pair.location.GetFastCGIPass();
	throw ConfigValues::DirectiveNotSetException("fastcgi_pass", host, target);
}