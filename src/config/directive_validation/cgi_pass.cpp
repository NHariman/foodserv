#include "cgi_pass.hpp"
CGIPass::CGIPass() : _is_set(false) {}

CGIPass::CGIPass(std::string input) : _is_set(true) {
	size_t start = 0;
	size_t end = 0;
	size_t set = 0;
	if (input.compare("") == 0)
		throw MissingArgumentsException();
	size_t  arguments = CountArguments(input);
	if (arguments > 2)
		throw TooManyArgumentsException();
	else if (arguments < 2)
		throw NotEnoughArgumentsException();
	for (size_t i = 0; i < input.size(); i++) {
		start = input.find_first_not_of(" \t\n\v\f\r", i);
		if (start == std::string::npos)
			break ;
		end = input.find_first_of(" \t\n\v\f\r", start);
		if (start == end)
			break ;
		if (set == 0) {
			_file_extension = input.substr(start, end - start);
			if (_file_extension[0] != '.')
				throw NotAFileExtensionException(_file_extension);
			set++;
		}
		else if (set == 1) {
			_executable_path = input.substr(start, end - start);
			set++;
			return ;
		}
		if (end == std::string::npos)
			break ;
		i = end;
	}
}

CGIPass::CGIPass(CGIPass const &obj) : 
_is_set(obj._is_set), _file_extension(obj._file_extension), _executable_path(obj._executable_path) {}

CGIPass& CGIPass::operator=(const CGIPass &obj) {
	if (this == &obj)
		return (*this);
	_is_set = obj._is_set;
	_file_extension = obj._file_extension;
	_executable_path = obj._executable_path;
	return (*this);
}


bool			CGIPass::IsSet() const {
	return _is_set;
}

std::string		CGIPass::GetFileExtension() const {
	return _file_extension;
}

std::string		CGIPass::GetExecutablePath() const {
	return _executable_path;
}

std::ostream& operator<<(std::ostream& os, const CGIPass& cgi_pass) {
	if (cgi_pass.IsSet() == false)
		os << "cgi_pass has not been set.";
	else {
		os << "cgi_pass extension: " << cgi_pass.GetFileExtension();
		os << "\nexecute with path: " << cgi_pass.GetExecutablePath();
	}
	return os;
}