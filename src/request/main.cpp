#include "request_parser.hpp"
#include <fstream> // ifstream TODO: REMOVE

int	main(int ac, char **argv) {
	if (ac < 2) {
		try {
			RequestParser parser("GET /hello.txt HTTP/1.1\nHost: www.example.com\n\n"); // use to test non-print chars
		}
		catch (std::exception &e) {
			cout << e.what() << endl;
			return 1;
		}
	}
	else {
		ifstream file(argv[1]);
		char buffer[30000] = {0};
		file.read(buffer, 3000);
		RequestParser request_parser;

		try {
			request_parser.Parse(buffer);
		}
		catch (std::exception &e) {
			cout << e.what() << endl;
			return 1;
		}
	}
	return 0;
}
