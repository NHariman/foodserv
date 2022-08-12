#include "setup.hpp"

// NginxConfig*    ConfigSetup(int ac, const char **av) {
//     try {
// 	    if (ac > 2) {
// 	    	throw TooManyArgumentsException();
// 	    }
// 		NginxConfig	config_file(av[1]);
//         return (&config_file);
//     }
// 	catch (const std::exception& e) {
// 		std::cerr << e.what() << '\n';
// 	}
//     return (NULL);
// }

void    ConfigSetup(int ac, const char **av, NginxConfig** config) {
    try {
	    // NginxConfig*	config_file;
		const char	*location;
	    if (ac > 2) {
	    	throw TooManyArgumentsException();
	    }
	    else if (ac == 1){
	    	location = "config_files/default.conf";
	    }
	    else {
	    	location = av[1];
	    }
		NginxConfig config_file(location);
		*config = &config_file;
    }
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
    // return (NULL);
}