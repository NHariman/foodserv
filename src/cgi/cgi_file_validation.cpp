#include "cgi.hpp"

// FILE COMPARING
// compares if the file locations are the same
// used in ValidScript();
bool		CGI::FileLocationCompare(std::string file_one, std::string file_two) {
	if (file_one.compare(file_two) == 0)
        return true;
    return false;
}

std::string		CGI::RemoveQuery(std::string path) {
	size_t end;
	end = path.find_first_of('?');
	return path.substr(0, end);
}

// checks if executable name is accurate regardless of prior path
// used in: SetCGIOneArgument(), SetExecutablePath()
bool		CGI::FileNameCompare(std::string file_one, std::string file_two) {
	if (_request->GetMethod().compare("GET") == 0) {
		file_one = RemoveQuery(file_one);
		file_two = RemoveQuery(file_two);
	}
	size_t i = file_one.size() - 1;
	size_t j = file_two.size() - 1;

	while (i > 0 && j > 0) {
		if (file_one[i] == file_two[j] && file_one[i] != '/') {
			i--;
			j--;
		}
		else if (file_one[i] == file_two[j] && file_one[i] == '/')
			return true;
		else {
			return false;
		}
	}
	if (i == j)
		return true;
	return false;
}

// EXTENSION FUNCTIONS
// validates if extensions are the same between the file and the cgi
// used in: SetCGITwoArguments()
bool	CGI::ValidateExtension(std::string *file) {
	// assumes the locationURI is the cgi file
	// checks if extension of the location URI matches
	// the allowed cgi_pass extension
	// and then assignes it
	if (HasExtension(_path) == true) {
		*file = _path;
		_valid_file = true;
		return true;
	}
	else {
		return false;
	}
}

// used in Validate Extension, checks if the extensions match
// used in: FindFile(), ValidateExtension()
bool		CGI::HasExtension(std::string file_name) {
	size_t i = file_name.size() - 1;
	size_t j = _CGI.GetFileExtension().size() - 1;

	while (j > 0 && i > 0) {
		if (file_name[i] == _CGI.GetFileExtension().at(j)) {
			j--;
			i--;
		}
		else {
			return false;
		}
	}
	if (j == 0)
		return true;
	return false;
}

// checks if script exists in the correct location and throws method if not
// used in: IsValidPath()
bool	CGI::ValidScript(std::string executable_path) {
	if (_CGI.GetLen() == 1 && IsDirectory(_path) == false && IsValidFile(_path) == true && FileLocationCompare(_path, executable_path) == false) {
		throw NotFoundException(); // file location not the same
		return false;
	}
	else
		_valid_file = true;
	return true;
}

// checks if path is executable or not
// used in ValidPath();
bool	CGI::IsExecutable(std::string path) {
	if (IsValidFile(path) == false && IsValidDirectory(path) == false) {
		throw NotFoundException(); // file does not exist
	}
	if (access(path.c_str(), X_OK) && _CGI.GetLen() == 1) {
		throw ForbiddenException(); // cannot execute
	}
	return true;
}

// checks if executable_path exists and is executable
// used in: SetExecutablePath()
bool	CGI::IsValidPath(std::string executable_path) {
	if (((IsValidFile(executable_path) || IsValidDirectory(executable_path))) && ValidScript(executable_path) == true)
		_valid_file = true;
	else
		throw NotFoundException();
	if (IsExecutable(executable_path) == false) {}
	return true;
}