#include "request_parser.hpp"
#include <fstream> // ifstream TODO: REMOVE

int	main(int ac, char **argv) {
	if (ac < 2) {
		cout << "Please provide request message\n";
		return 1;
	}

	ifstream file(argv[1]);
	char buffer[30000] = {0};
	file.read(buffer, 3000);
	RequestParser request_parser;

	try {
		request_parser.Parse(buffer);
	}
	catch (BadRequestException &e) {
		cout << e.what() << endl;
		return 1;
	}
	return 0;
}
