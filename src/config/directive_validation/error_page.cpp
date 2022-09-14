// input: 404             /404.html
// input: 500 502 503 504 /50x.html

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
#include "error_page.hpp"


void	AddToErrorPageMap(std::map<int, std::string> *map, std::string input) {
	int code;

	if (input.compare("") == 0)
		throw ErrorPage::MissingArgumentsException();

	std::vector<std::string> items = ToStringVector(input);

	std::string uri = items[items.size() - 1];
	if (IsUri(uri) == false)
		throw ErrorPage::BadErrorURIException();
	for (size_t i = 0; i < (items.size() - 1); ++i) {
		if (IsNumber(items[i]) == true) {
			code = std::atoi(items[i].c_str());
			if (code < 300 || code > 599)
				throw ErrorPage::BadErrorCodeException();
			std::map<int,std::string>::iterator it = map->find(code);
			if (it == map->end())
				map->insert(std::pair<int, std::string> (code, uri));
			else
				throw ErrorPage::DuplicateErrorCodeException();
		}
		else
			throw ErrorPage::InvalidCodeInputException();
	}
}
