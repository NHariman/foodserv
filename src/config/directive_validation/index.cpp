#include "index.hpp"
#include <iostream>

Index::Index(std::string value) {
	if (value.compare("") == 0)
		throw MissingArgumentsException();
	_index = ToStringVector(value);
}

std::vector<std::string>	Index::GetIndex() const {
	return _index;
}

void		Index::PrintIndex() {
	for (size_t i = 0; i < _index.size(); i++)
		std::cout << _index.at(i) << std::endl;
}

