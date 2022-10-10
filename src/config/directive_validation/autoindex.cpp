#include "autoindex.hpp"

bool SetAutoindex(std::string value) {

	if (value.compare("") == 0)
		throw Autoindex::MissingArgumentsException();
	if (CountArguments(value) > 1)
		throw Autoindex::TooManyArgumentsException();
	if (value.compare("on") != 0 && value.compare("off") != 0)
		throw Autoindex::InvalidAutoindexException();
	if (value.compare("on") == 0)
		return true;
	else if (value.compare("off") == 0)
		return false;
	throw Autoindex::InvalidAutoindexException();
}
