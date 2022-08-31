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
