#include "return_dir.hpp"
#include "../../utils/config_utils.hpp"

ReturnDir::ReturnDir() : _is_set(false) {}

void	ReturnDir::SetReturnCode(std::string key) {
	_code = ft_atosize_t(key);
	if (!IsValidReturnCode(_code))
			throw InvalidReturnCodeException(key);
}

void	ReturnDir::SetVariables(std::string key, size_t *set) {
	if (IsNumber(key) == false && *set == 0)
		throw InvalidReturnCodeException(key);
	if (*set == 0) {
		SetReturnCode(key);
		*set = *set + 1;
	}
	else if (*set > 1)
		throw InvalidAmountOfArgumentsException();
	else{
		_url = key;
		*set = *set + 1;
	}
}

void	ReturnDir::FillReturn(std::string input) {
	size_t	i = 0;
	size_t	start = 0;
	size_t	end = 0;
	std::string key;
	size_t	set = 0;

	while (input[i]){
		start = input.find_first_not_of(" \t\n\v\f\r", i);
		if (start == std::string::npos)
			break ;
		end = input.find_first_of(" \t\n\v\f\r", start);
		key = input.substr(start, end - start);
		SetVariables(key, &set);
		if (end == std::string::npos)
			break ;
		i = end;
	}
}

ReturnDir::ReturnDir(std::string input) : _is_set(true) {
	if (input.compare("") == 0)
		throw MissingArgumentsException();
	FillReturn(input);
}

ReturnDir::ReturnDir(ReturnDir const &obj) :
_is_set(obj._is_set), _code(obj._code), _url(obj._url) {}

ReturnDir&		ReturnDir::operator= (ReturnDir const &obj) {
	if (this == &obj)
		return (*this);
	_is_set = obj._is_set;
	_code = obj._code;
	_url = obj._url;
	return (*this);
}

bool	ReturnDir::IsSet() const {
	return _is_set;
}

int		ReturnDir::GetCode() const {
	return _code;
}

std::string	ReturnDir::GetUrl() const {
	return _url;
}

bool ReturnDir::IsValidReturnCode(size_t code) {
	if (code < 0 || code > 999)
		return false;
	return true;
}

std::ostream&		operator<<(std::ostream& os, const ReturnDir& obj) {
	if (obj.IsSet() == false)
		os << "Return was not set.";
	else {
		os << "Return dir code: " << obj.GetCode();
		os << "\nReturn dir url: " << obj.GetUrl();
	}
	return os;
}