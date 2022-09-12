// LocationUri				    _location_uri;
// bool					    _autoindex;
// std::string				    _root;
// std::vector<std::string>	_index;
// int					        _client_max_body_size;
// std::vector<ErrorPage>		_error_page;
// CGIPass					    _cgi_pass;
// AllowedMethods				_allowed_methods;
// ReturnDir				    _return_dir;

/*
    DIRECTIVE THAT CAN BE IN OUR LOCATION CONTEXT:
    - cgi pass
    - allowed methods
    - alias
    - autoindex
    - root
    - index
    - client max body size
    - error page
*/

// starting with root:
// if root is set WITHIN the location: use that root
// if root is not set within the location, but it is in the server, use that root
// if root is not set at all: check if default is /

// create some kind of slash check function, that will merge double slashes

#ifndef RESOLVED_PATH
# define RESOLVED_PATH

#include "target_config.hpp"
#include <algorithm>

class TargetConfig;

class ResolvedPath {

    private:
        std::string		_path;
		TargetConfig	*_target_config;

		std::string		_locationblock_uri;
		std::string		_request_uri;
        
        void    AppendRoot();
        void	ReplaceAlias();
        void    ReplaceReturn();
		int		CharOccurence(std::string str, char c);

    public:
        ResolvedPath(TargetConfig *target_config, std::string target);

};

#endif
