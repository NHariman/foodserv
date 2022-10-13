#include "cgi.hpp"

#define DEBUG 1

// searches directory for file with the right extension and returns it
// otherwise throws file not found
std::string CGI::FindFile() {
	struct dirent *directory;
	std::string file;
	size_t status_code = 404;
	DIR *dr = opendir(_path.c_str());
	if (dr == NULL) {
		throw NotFoundException();
	}
	while ((directory = readdir(dr)) != NULL) {
		if (HasExtension(directory->d_name)) {
			_file_name = directory->d_name;
			file = _path + directory->d_name;
			_valid_file = true;
			status_code = 200;
			break ;
		}
		status_code = 404;
		_valid_file = false;
	}
	closedir(dr);
	if (status_code == 404)
		throw NotFoundException();
	return (file);
}

// the cgi_pass directive is providing a CGI executable
// make the absolute path
// check if resolved path is a directory or a file
// if file, check if resolved path filename matches cgi executable path
void		CGI::SetCGIOneArgument() {
	_file_name = SetExecutablePath();
	if (DEBUG) std::cout << "_request->GetTargetURI().GetParsedURI(): " << _request->GetTargetURI().GetParsedURI() << std::endl;
	if (IsDirectory(_request->GetTargetURI().GetParsedURI()) == false && FileNameCompare(_request->GetTargetURI().GetParsedURI(), _file_name) == false) {
		throw NotFoundException();
	}
	_argv.push_back(_file_name);
}

// cgi_pass directive provides a cgi extension and an executable to execute it with
// first bit is the same
// second bit finds either the first cgi file
// OR compares the extension with the requested file
void	CGI::SetCGITwoArguments() {
	std::string first_arg;
	std::string second_arg;
	first_arg = SetExecutablePath();
	_argv.push_back(first_arg);
	if(_TARGET.GetLocationUri().IsDir() == true && IsDirectory(_request->GetTargetURI().GetParsedURI()) == true) {
		// if location match & request target URI is a directory, find file in said directory
		second_arg = FindFile();
	}
	else {
		if (DEBUG) std::cout << "validate extension" << std::endl;
		if (ValidateExtension(&second_arg) == false) // extension incompatible
			throw NotFoundException();
	}
	_file_name = second_arg; // change _file_name to 2nd argument in argv
	_argv.push_back(second_arg);

}

// sets executable path based on request, location target and if the executable path is absolute or relative
std::string CGI::SetExecutablePath() {
	std::string executable_path;

	if (!IsAbsolutePath(_CGI.GetExecutablePath())) {
		if (_TARGET.GetLocationUri().IsDir() == true && IsDirectory(_request->GetTargetURI().GetParsedURI()) == true)
			executable_path = MakeAbsolutePath(_CGI.GetExecutablePath(), _path); // path is not a file, so you can append the executable to it
		else if (!IsDirectory(_path)) {
			if (FileNameCompare(_path, _CGI.GetExecutablePath()) == false)
				throw NotFoundException();
			executable_path = _path; // path is a file, no need for appending
		}
		else
			executable_path = _CGI.GetExecutablePath(); // use relative cgi path
	}
	else
		executable_path = _CGI.GetExecutablePath(); // use absolute cgi path

	IsValidPath(executable_path); // checks if the file exists and is executable
	if (DEBUG) std::cout << "executable_path: " << executable_path << std::endl;
	if (DEBUG) std::cout << std::boolalpha << _valid_file << std::endl;
	return (executable_path);
}

#undef DEBUG