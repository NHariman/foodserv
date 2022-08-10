#include "setup.hpp"

NginxConfig*    ConfigSetup(int ac, const char **av) {
    try {
	    NginxConfig*	config_file;
	    if (ac > 2) {
	    	throw TooManyArgumentsException();
	    }
	    else if (ac == 2){
	    	NginxConfig		location;
	    	config_file = &location;
	    }
	    else {
	    	NginxConfig		location(av[1]);
	    	config_file = &location;
	    }
        return (config_file);
    }
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
    return (NULL);
}