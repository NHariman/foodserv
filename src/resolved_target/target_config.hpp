#ifndef TARGET_CONFIG_HPP
# define TARGET_CONFIG_HPP

#include "../config/config_interface.hpp"
#include "../config/nginx_config.hpp"
#include "../config/server_context.hpp"
#include "../config/location_context.hpp"
#include "server_selection.hpp"
#include "location_selection.hpp"
#include "resolved_path.hpp"


# define GET 0
# define POST 1
# define DELETE 2

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

		// unique
		ServerContext						_server;
		LocationContext						_location;
		std::string							_resolved_path;		
*/

// grandparent inheritance 
// https://stackoverflow.com/questions/50728384/inherit-parent-privately-while-inheriting-its-grandparent-publicly-in-c

class TargetConfig : public LocationContext, virtual public ConfigValues {
	private:
		std::string     					SetRoot(ServerContext *server, LocationContext *location);
		std::vector<std::string>			SetIndex(ServerContext *server, LocationContext *location);
		size_t								SetMaxBodySize(ServerContext *server, LocationContext *location);
		std::vector<ErrorPage>				SetErrorPage(ServerContext *server, LocationContext *location);
		bool								SetAutoindex(ServerContext *server, LocationContext *location);
		ReturnDir							SetReturn(ServerContext *server, LocationContext *location);

		ServerContext						_server;
		LocationContext						_location;
		std::string							_resolved_path;
	
	public:
		TargetConfig(){};
		virtual ~TargetConfig(){};
		void	Setup(NginxConfig *config, std::string host, std::string port, std::string target);
		
		//getters
		bool						IsAllowedMethod(std::string method);
		CGIPass						GetCGIPass() const;
		std::string					GetRoot() const;
		std::vector<std::string> 	GetIndex() const;
		size_t						GetMaxBodySize() const;
		std::vector<ErrorPage>		GetErrorPage() const;
		bool						GetAutoindex() const;
		ReturnDir 					GetReturn() const;
		std::string					GetAlias() const;
		std::string					GetResolvedPath() const;

		ServerContext				GetServer() const;
		LocationContext				GetLocation() const;
};


#endif