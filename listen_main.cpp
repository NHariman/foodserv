#include "src/config/listen.hpp"

int     main() {
	try {
		Listen  test1("127.0.0.1:8000");
		std::cout << "test1 IP: " << test1.getIpNumber() << " port: " << test1.getPortNumber() << std::endl;
		
		Listen  test2("8000");
		std::cout << "test2 IP: " << test2.getIpNumber() << " port: " << test2.getPortNumber() << std::endl;

		Listen  test3("*:8000");
		std::cout << "test3 IP: " << test3.getIpNumber() << " port: " << test3.getPortNumber() << std::endl;

		Listen  test4("localhost:8000");
		std::cout << "test4 IP: " << test4.getIpNumber() << " port: " << test4.getPortNumber() << std::endl;

		Listen  test5("localhost");
		std::cout << "test5 IP: " << test5.getIpNumber() << " port: " << test5.getPortNumber() << std::endl;

		Listen  test6("[::]:8000");
		std::cout << "test6 IP: " << test6.getIpNumber() << " port: " << test6.getPortNumber() << std::endl;

		Listen  test7("[::1]");
		std::cout << "test7 IP: " << test7.getIpNumber() << " port: " << test7.getPortNumber() << std::endl;

		Listen  test8("127.0.0.1");
		std::cout << "test8 IP: " << test8.getIpNumber() << " port: " << test8.getPortNumber() << std::endl;

		Listen	test9("");
		std::cout << "test9 IP: " << test9.getIpNumber() << " port: " << test9.getPortNumber() << std::endl;

		Listen	test10("crap");
		std::cout << "test10 IP: " << test10.getIpNumber() << " port: " << test10.getPortNumber() << std::endl;

		Listen	test11("cra:p");
		std::cout << "test11 IP: " << test11.getIpNumber() << " port: " << test11.getPortNumber() << std::endl;

	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}


}

