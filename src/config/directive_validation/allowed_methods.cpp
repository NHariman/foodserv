#include "allowed_methods.hpp"
#include <iostream>
#include <algorithm>

AllowedMethods::AllowedMethods() : _is_set(false) {}

AllowedMethods::AllowedMethods(std::string str) {
	const std::string	key_name[] = {"GET", "POST", "DELETE"};
	int	is_key = 0;

	if (str.compare("") == 0)
		throw MissingArgumentsException();
	_methods = ToStringVector(str);
	for (size_t i = 0; i < _methods.size(); i++) {
		std::string key;
		is_key = std::find(key_name, key_name + 3, _methods.at(i)) - key_name;
		if (is_key < 0 || is_key > 2)
			throw BadMethodException();
	}
	_is_set = true;
}

AllowedMethods::AllowedMethods(AllowedMethods const &obj) {
	_is_set = obj.IsSet();
	for (size_t i = 0; i < obj.GetAllowedMethods().size() ; i++) {
		_methods.push_back(obj.GetAllowedMethods().at(i));
	}
}

AllowedMethods&		AllowedMethods::operator=(AllowedMethods const &obj) {
	if (this == &obj)
		return (*this);
	_is_set = obj.IsSet();
	for (size_t i = 0; i < obj.GetAllowedMethods().size() ; i++) {
		_methods.push_back(obj.GetAllowedMethods().at(i));
	}
	return (*this);
}

std::vector<std::string>	AllowedMethods::GetAllowedMethods() const {
	if (_methods.empty() || _is_set == false)
		throw EmptyMethodVectorException();
	return _methods;
}

void		AllowedMethods::PrintMethods() {
	for (size_t i = 0; i < _methods.size(); i++)
		std::cout << _methods.at(i) << std::endl;
}

bool		AllowedMethods::IsSet() const {
	return _is_set;
}
