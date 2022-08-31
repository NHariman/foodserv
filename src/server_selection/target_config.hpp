#ifndef TARGET_CONFIG_HPP
# define TARGET_CONFIG_HPP

#include "../config/config_interface.hpp"
#include "../config/nginx_config.hpp"
#include "../config/server_context.hpp"
#include "../config/location_context.hpp"
#include "get_host.hpp"

# define GET 0
# define POST 1
# define DELETE 2

// grandparent inheritance 
// https://stackoverflow.com/questions/50728384/inherit-parent-privately-while-inheriting-its-grandparent-publicly-in-c

class TargetConfig : public LocationContext, virtual public ConfigValues {
	private:
		std::string     					RetrieveRoot(ServerContext *server, LocationContext *location);
		std::vector<std::string>			RetrieveIndex(ServerContext *server, LocationContext *location);
		size_t								RetrieveMaxBodySize(ServerContext *server, LocationContext *location);
		std::vector<ErrorPage>				RetrieveErrorPage(ServerContext *server, LocationContext *location);
		bool								RetrieveAutoindex(ServerContext *server, LocationContext *location);
		ReturnDir							RetrieveReturn(ServerContext *server, LocationContext *location);

		CGIPass								RetrieveCGIPass(ServerContext *server, LocationContext *location);
	public:
		TargetConfig(){};
		virtual ~TargetConfig(){};
		void	SetupTargetConfig(std::string host, std::string port, std::string target, NginxConfig *config);
		//getters
		bool						IsAllowedMethod(std::string method);
		std::string					GetRoot() const;
		std::vector<std::string> 	GetIndex() const;
		size_t						GetMaxBodySize() const;
		std::vector<ErrorPage>		GetErrorPage() const;
		bool						GetAutoindex() const;
		ReturnDir 					GetReturn() const;
};

ServerContext			GetHost(std::string host, NginxConfig *config);
LocationContext			GetTarget(ServerContext *server, std::string target);


#endif