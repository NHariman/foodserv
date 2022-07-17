#include "allowed_methods.hpp"
#include <iostream>
#include <algorithm>

AllowedMethods::AllowedMethods(std::string str) {
	const std::string	key_name[] = {"GET", "POST", "DELETE"};
	int	is_key = 0;

	_methods = ToStringVector(str);
	for (size_t i = 0; i < _methods.size(); i++) {
		std::string key;
		is_key = std::find(key_name, key_name + 3, _methods.at(i)) - key_name;
		if (is_key < 0 || is_key > 2)
			throw BadMethodException();
	}
}

std::vector<std::string>	AllowedMethods::GetAllowedMethods() const {
	return _methods;
}

void		AllowedMethods::PrintMethods() {
	for (size_t i = 0; i < _methods.size(); i++)
		std::cout << _methods.at(i) << std::endl;
}

// int			main(){
// 	AllowedMethods	test("POST GET DELETE");

// 	test.PrintMethods();
// 	return 0;
// }