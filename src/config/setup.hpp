#ifndef SETUP_HPP
# define SETUP_HPP

#include "nginx_config.hpp"
#include <iostream>
#include <stdexcept>
#include "config_exeptions.hpp"

NginxConfig*    ConfigSetup(int ac, const char **av);

#endif