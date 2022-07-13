#include "listen.hpp"
#include "server_name.hpp"

/*
options: 
- An IP address/port combo.
- A lone IP address which will then listen on the default port 80.
- A lone port which will listen to every interface on that port.
default: 0.0.0.0 and 80
possible listen directives:
listen 0.0.0.0:80;
listen 0.0.0.0:8080;
listen 80;
listen 0.0.0.0;
listen :80;
listen 0.0.0.0:
*/

void	listen_test() {
		Listen		test_listen("false");
	std::cout << "test_listen - IP: " << test_listen.getIpNumber() << " - Port: " << test_listen.getPortNumber() << std::endl << std::endl; 

	Listen		test_listen2("0.0.0.0:80");
	std::cout << "test_listen2 - IP: " << test_listen2.getIpNumber() << " - Port: " << test_listen2.getPortNumber() << std::endl << std::endl; 

	Listen		test_listen3(":80");
	std::cout << "test_listen3 - IP: " << test_listen3.getIpNumber() << " - Port: " << test_listen3.getPortNumber() << std::endl << std::endl; 

	Listen		test_listen4("0.0.0.0:");
	std::cout << "test_listen4 - IP: " << test_listen4.getIpNumber() << " - Port: " << test_listen4.getPortNumber() << std::endl << std::endl; 
	
	Listen		test_listen5("80:0.0.0.0"); // false
	std::cout << "test_listen5 - IP: " << test_listen5.getIpNumber() << " - Port: " << test_listen5.getPortNumber() << std::endl << std::endl; 

	Listen		test_listen6("255.0.0.1:6610");
	std::cout << "test_listen6 - IP: " << test_listen6.getIpNumber() << " - Port: " << test_listen6.getPortNumber() << std::endl << std::endl; 
	// ServerName test;

	Listen		test_listen7("0.0.0.0");
	std::cout << "test_listen7 - IP: " << test_listen7.getIpNumber() << " - Port: " << test_listen7.getPortNumber() << std::endl << std::endl;

	Listen		test_listen8("80");
	std::cout << "test_listen8 - IP: " << test_listen8.getIpNumber() << " - Port: " << test_listen8.getPortNumber() << std::endl << std::endl; 
}

void	server_test() {
	ServerName	test("host1.example.com");
	test.PrintServerNamesVector();
	std::cout << std::endl;

	ServerName	test2("example.com");
	test2.PrintServerNamesVector();
	std::cout << std::endl;

	ServerName	test3("example.org www.example.org");
	test3.PrintServerNamesVector();
	std::cout << std::endl;
	
	ServerName	test4("domain1.com domain1.nl domain1.*");
	test4.PrintServerNamesVector();
	std::cout << std::endl;

	ServerName	test5("");
	test5.PrintServerNamesVector();
	std::cout << std::endl;

	ServerName	test6("    example1");
	test6.PrintServerNamesVector();
}

int		main() {

	// listen_test();

	server_test();
}