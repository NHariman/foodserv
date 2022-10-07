#ifndef LISTEN_HPP
# define LISTEN_HPP

#include <iostream>
#include <string>
#include <exception> 
#include <arpa/inet.h>
#include <netdb.h>

# define DEFAULT_PORT "80"
# define DEFAULT_IP	"127.0.0.1"

class Listen {
	private:
		std::string	_listen;
		std::string	_port_number;
		std::string	_ip_address;
		
	private:
		Listen();
		Listen(const Listen& x);
		Listen& operator=(const Listen& rhs);

	public:
		Listen(std::string listen);
		
		void		SplitPortIP();
		void		CheckPortNumber(std::string port_number);
		void		CheckIpAddress(std::string ip_address);
		bool		CheckValidAddress(std::string ip_to_check);
		std::string	getPortNumber();
		std::string	getIpNumber();

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
