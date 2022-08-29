/*
 __      _____| |__  ___  ___ _ ____   __ 
 \ \ /\ / / _ \ '_ \/ __|/ _ \ '__\ \ / /   
  \ V  V /  __/ |_) \__ \  __/ |   \ V /  
   \_/\_/ \___|_.__/|___/\___|_|    \_/   
   
   The Listen class checks the listen directive from the configuratin file.
   - 
*/

#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <iostream>
#include <string>
#include <exception> 

/*
**	NOTES:
**	The listen directive 
**	- port cant be negative and not bigger than 65535
*/

class Listen {
	private:
		std::string	_listen;
		std::string	_port_number;
		std::string	_ip_number;
		
	private:
		Listen();
		Listen(const Listen& x);
		Listen& operator=(const Listen& rhs);

	public:
		Listen(std::string listen);
		
		bool		CheckCharacters();
		bool		SplitPortIP();
		bool		CheckPortNumber(std::string port_number);
		bool		CheckIpAddress(std::string ip_address);
		std::string	getPortNumber();
		std::string	getIpNumber();

		/* exceptions */

		class InvalidPortException : public std::exception {
			public:
				const char *what() const throw () {
					return "ERROR! Invalid port number detected.";
				}
		};

		class InvalidIpException : public std::exception {
			public:
				const char *what() const throw() {
					return "ERROR! Invalid IP detected.";
				}
		};
};

#endif
