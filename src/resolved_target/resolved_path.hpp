#ifndef RESOLVED_PATH
# define RESOLVED_PATH

#include "target_config.hpp"
#include "../utils/utils.hpp"
#include <algorithm>

class TargetConfig;

class ResolvedPath {

    private:
        std::string		_path;
		TargetConfig	*_target_config;

		std::string		_locationblock_uri;
		std::string		_request_uri;

        
        bool    CheckReturn();
        void    AppendRoot();
        void	ReplaceAlias();

		// int		CharOccurence(std::string str, char c);

    public:
        ResolvedPath(TargetConfig *target_config);
        std::string	    Resolve(std::string target, std::string method);
        std::string     GetResolvedPath() const;
        void	        RequestIsValidDirectory();
        std::string     SearchIndexFiles();
        void            CleanUpPath();
        bool	        LocationIsDirectory() const;

};

#endif
