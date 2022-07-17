#include "index.hpp"
#include <iostream>

Index::Index(std::string value) {
	_index = ToStringVector(value);
}

std::vector<std::string>	Index::GetIndex() const {
	return _index;
}

void		Index::PrintIndex() {
	for (size_t i = 0; i < _index.size(); i++)
		std::cout << _index.at(i) << std::endl;
}

// int			main(){
// 	Index	test("index.php index.html index.htm index.nginx-debian.html");

// 	test.PrintIndex();
// 	return 0;
// }
