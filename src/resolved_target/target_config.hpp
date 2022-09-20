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

class ResolvedPath;

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

		// all have getters	
*/

// grandparent inheritance 
// https://stackoverflow.com/questions/50728384/inherit-parent-privately-while-inheriting-its-grandparent-publicly-in-c

class TargetConfig : public LocationContext, virtual public ConfigValues {
	private:
		std::string     					SetRoot(ServerContext *server, LocationContext *location);
		std::vector<std::string>			SetIndex(ServerContext *server, LocationContext *location);
		size_t								SetMaxBodySize(ServerContext *server, LocationContext *location);
		std::map<int, std::string>			SetErrorPage(ServerContext *server, LocationContext *location);
		bool								SetAutoindex(ServerContext *server, LocationContext *location);
		ReturnDir							SetReturn(ServerContext *server, LocationContext *location);

		ServerContext						_server;
		LocationContext						_location;
		std::string							_resolved_path;
		bool								_generate_index;

	
	public:
		TargetConfig(){};
		virtual ~TargetConfig(){};
		TargetConfig&	operator= (TargetConfig const &obj);
		void	Setup(NginxConfig *config, std::string host, std::string port, std::string target);

		void	SetGenerateIndexBool(bool index);
		
		//getters
		bool						IsAllowedMethod(std::string method);
		size_t						GetMaxBodySize() const;
		bool						MustGenerateIndex() const;

		std::string					GetResolvedPath() const;
		ServerContext				GetServer() const;
		LocationContext				GetLocation() const;
};


#endif