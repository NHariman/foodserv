#include "src/config/listen.hpp"

int     main() {
	try {
		Listen  test1("127.0.0.1:8000");
		Listen  test2("8000");
		Listen  test3("*:8000");
		Listen  test4("localhost:8000");
		Listen  test5("localhost");
		Listen  test6("[::]:8000");
		Listen  test7("[::1]");
		Listen  test8("127.0.0.1");
		Listen	test9("");

		Listen	test10("crap");
		Listen	test11("cra:p");
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

