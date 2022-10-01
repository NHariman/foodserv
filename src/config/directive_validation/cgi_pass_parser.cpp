#include "cgi_pass.hpp"

void    CGIPass::OneArgument(std::string input) {
    size_t start = 0;
    size_t end = 0;

	start = input.find_first_not_of(" \t\n\v\f\r");
	end = input.find_first_of(" \t\n\v\f\r", start);
	_executable_path = input.substr(start, end - start);
	if (IsPath(_executable_path) == false)
		throw NotAPathException(_executable_path);
}

void    CGIPass::SetExtension(std::string input) {
    _file_extension = input;
	if (_file_extension[0] != '.')
		throw NotAFileExtensionException(_file_extension);
}

void    CGIPass::SetExecutableTwoArg(std::string input) {
    _executable_path = input;
	if (IsPath(_executable_path) == false)
		throw NotAPathException(_executable_path);
}

void    CGIPass::TwoArguments(std::string input) {
    size_t start = 0;
    size_t end = 0;
    size_t set = 0;

    for (size_t i = 0; i < input.size(); i++) {
		start = input.find_first_not_of(" \t\n\v\f\r", i);
		if (start == std::string::npos)
			break ;
		end = input.find_first_of(" \t\n\v\f\r", start);
		if (start == end)
			break ;
		if (set == 0) {
            SetExtension(input.substr(start, end - start));
			set++;
		}
		else if (set == 1) {
			SetExecutableTwoArg(input.substr(start, end - start));
			set++;
			return ;
		}
		if (end == std::string::npos)
			break ;
		i = end;
	}
}