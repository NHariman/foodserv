#include "allowed_methods.hpp"

int		IsValidHTTPMethod(std::string method) {
	const std::string	methods[] = {"GET", "POST", "DELETE"};
	int is_method = std::find(methods, methods + 3, method) - methods;
	if (is_method < 0 || is_method > 2)
		throw AllowedMethods::BadMethodException();
	return (is_method);
}


AllowedMethods::AllowedMethods() : _get(false), _post(false), _delete(false) {}

AllowedMethods::AllowedMethods(std::string str) : _get(false), _post(false), _delete(false) {
	if (str.compare("") == 0)
		throw MissingArgumentsException();
	size_t	arguments = CountArguments(str);
	if (arguments > 3)
		throw TooManyArgumentsException();
	std::vector<std::string>methods = ToStringVector(str);
	for (size_t i = 0; i < methods.size(); i++) {
		switch (IsValidHTTPMethod(methods.at(i))) {
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
