#include "allowed_methods.hpp"

AllowedMethods::AllowedMethods() : _get(false), _post(false), _delete(false) {}

AllowedMethods::AllowedMethods(std::string str) : _get(false), _post(false), _delete(false) {

	if (str.compare("") == 0)
		throw MissingArgumentsException();
	size_t	arguments = CountArguments(str);
	if (arguments > 3)
		throw TooManyArgumentsException();
	_methods = ToStringVector(str);
	ValidateMethods();
}

AllowedMethods::AllowedMethods(AllowedMethods const &obj) : 
_get(obj._get), 
_post(obj._post), 
_delete(obj._delete),
_methods(obj._methods) {}

AllowedMethods&		AllowedMethods::operator=(AllowedMethods const &obj) {
	if (this == &obj) {
		return (*this);
	}
	_get = obj._get;
	_post = obj._post;
	_delete = obj._delete;
	_methods = obj._methods;
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

std::vector<std::string>	AllowedMethods::GetMethods() const {
	return _methods;
}

void		AllowedMethods::ValidateMethods() {
	for (size_t i = 0; i < _methods.size(); i++) {
		if (_methods.at(i).empty())
			break ;
		switch (IsValidHTTPMethod(_methods.at(i))) {
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
