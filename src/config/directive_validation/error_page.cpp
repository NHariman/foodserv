// input: 404             /404.html
// input: 500 502 503 504 /50x.html

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
#include "error_page.hpp"

ErrorPage::ErrorPage() : _is_set(false) {}

ErrorPage::ErrorPage(std::string input) : _is_set(true) {
	size_t	i = 0;
	size_t	start = 0;
	size_t	end = 0;
	std::string key;
	int			code;

	if (input.compare("") == 0)
		throw MissingArgumentsException();
	while (input[i]) {
		start = input.find_first_not_of(" \t\n\v\f\r", i);
		end = input.find_first_of(" \t\n\v\f\r", start);
		if (start == end)
			break ;
		key = input.substr(start, end - start);
		if (IsNumber(key) == true) {
			if (_uri.empty() == false)
				throw InvalidInputException();
			code = std::atoi(key.c_str());
			if (code < 300 || code > 599)
				throw BadErrorCodeException();
			_code.push_back(code);
		}
		else if (IsUri(key) == true) {
			if (_uri.empty() == true)
				_uri = key;
			else
				throw DuplicateUriException();
		}
		else
			throw InvalidInputException();
		i = end;
	}
}

ErrorPage::ErrorPage(ErrorPage const &obj) :
_is_set(true), _uri(obj._uri), _code(obj._code) {
}

ErrorPage&	ErrorPage::operator=(ErrorPage const & obj) {
	if (this == &obj){
		return (*this);
	}
		_is_set = obj._is_set;
		_uri = obj._uri;
		_code = obj._code;
	return (*this);
}

void			ErrorPage::PrintCodes() const {
	for (size_t i = 0; i < _code.size(); i++) {
		std::cout << _code.at(i) << std::endl;
	}
}

std::string		ErrorPage::GetUri() const {
	return _uri;
}

std::vector<int>		ErrorPage::GetCodes() const {
	return _code;
}

std::ostream& operator<<(std::ostream& os, const ErrorPage& error_page) {
	os << "Uri: " << error_page.GetUri() << "\n" << "Error Codes:\n";
	for (size_t i = 0; i < error_page.GetCodes().size(); i++) {
		os << error_page.GetCodes().at(i) << std::endl;
	}
	return os;
}
