#include "autoindex.hpp"

bool SetAutoindex(std::string value) {

	if (value.compare("") == 0)
		throw Autoindex::MissingArgumentsException();
	size_t  arguments = CountArguments(value);
	if (arguments != 1)
		Autoindex::TooManyArgumentsException();
	if (value.compare("on") != 0 && value.compare("off") != 0)
		throw Autoindex::InvalidAutoindexException();
	if (value.compare("on") == 0)
		return true;
	else if (value.compare("off") == 0)
		return false;
	throw Autoindex::InvalidAutoindexException();
}
