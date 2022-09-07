#include "get_host.hpp"

ServerContext			GetHost(std::string host, NginxConfig *config) {

	for (size_t server = 0 ; server < config->GetServers().size(); server++) {
		for(size_t names = 0 ; names < config->GetServers().at(server).GetServerNameVector().at(names).size() ; names++) {
			if (host.compare(config->GetServers().at(server).GetServerNameVector().at(names)) == 0) {
				return config->GetServers().at(server);
			}
		}
	}
	return config->GetServers().at(0);
}

LocationContext			GetTarget(ServerContext *server, std::string target) {
	for (size_t loc = 0 ; loc < server->GetLocationContexts().size() ; loc++) {
		if (target.compare(server->GetLocationContexts().at(loc).GetLocationUri().GetUri()) == 0) {
			return (server->GetLocationContexts().at(loc));
			}
	}
	return (GetTarget(server, "/"));
}