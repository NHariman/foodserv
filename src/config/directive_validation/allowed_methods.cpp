#include "allowed_methods.hpp"


AllowedMethods::AllowedMethods() : _get(false), _post(false), _delete(false) {}

AllowedMethods::AllowedMethods(std::string str) : _get(false), _post(false), _delete(false) {
	const std::string	key_name[] = {"GET", "POST", "DELETE"};
	int	is_key = 0;

	if (str.compare("") == 0)
		throw MissingArgumentsException();
	size_t	arguments = CountArguments(str);
	if (arguments > 3)
		throw TooManyArgumentsException();
	std::vector<std::string>methods = ToStringVector(str);
	for (size_t i = 0; i < methods.size(); i++) {
		std::string key;
		is_key = std::find(key_name, key_name + 3, methods.at(i)) - key_name;
		if (is_key < 0 || is_key > 2)
			throw BadMethodException();
		switch (is_key) {
			case 0:
				_get = true;
				break ;
			case 1:
				_post = true;
				break ;
			case 2:
				_delete = true;
				break ;
		}
	}
}

AllowedMethods::AllowedMethods(AllowedMethods const &obj) : 
_get(obj._get), 
_post(obj._post), 
_delete(obj._delete) {}

AllowedMethods&		AllowedMethods::operator=(AllowedMethods const &obj) {
	if (this == &obj) {
		return (*this);
	}
	_get = obj._get;
	_post = obj._post;
	_delete = obj._delete;
	return (*this);
}

bool	AllowedMethods::GetGET() const {
	return _get;
}

bool	AllowedMethods::GetPOST() const {
	return _post;
}
bool	AllowedMethods::GetDELETE() const {
	return _delete;
}
