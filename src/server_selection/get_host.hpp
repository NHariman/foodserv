#ifndef GET_HOST_HPP

# define GET_HOST_HPP

#include <string>
#include <stdexcept>
#include "../config/nginx_config.hpp"
#include "../config/server_context.hpp"

ServerContext			GetHost(std::string host, NginxConfig *config);


#endif