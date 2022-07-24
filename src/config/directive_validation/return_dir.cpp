#include "return_dir.hpp"
#include "../config_utils.hpp"

ReturnDir::ReturnDir(std::string input) {
	size_t	i = 0;
	size_t	start = 0;
	size_t	end = 0;
	std::string key;
	size_t	set = 0;

	if (input.compare("") == 0)
		throw MissingArgumentsException();
	while (input[i]){
		start = input.find_first_not_of(" \t\n\v\f\r", i);
		end = input.find_first_of(" \t\n\v\f\r", start);
		if (start == end)
			break ;
		key = input.substr(start, end - start);
		if (IsNumber(key) && set == 0)
			throw InvalidReturnCodeException();
		if (set == 0) {
			_code = ft_atol(key);
			set++;
		}
		else if (set > 2)
			throw InvalidAmountOfArgumentsException();
		else{
			_url = key;
			set++;
		}
		i = end;
	}
}

ReturnDir::ReturnDir(ReturnDir const &obj) {
	_code = obj.GetCode();
	_url = obj.GetUrl();
}

ReturnDir&		ReturnDir::operator= (ReturnDir const &obj) {
	if (this == &obj)
		return (*this);
	_code = obj.GetCode();
	_url = obj.GetUrl();
	return (*this);
}

int		ReturnDir::GetCode() const {
	return _code;
}

std::string	ReturnDir::GetUrl() const {
	return _url;
}