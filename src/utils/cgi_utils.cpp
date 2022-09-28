#include "cgi_utils.hpp"

bool	IsPath(std::string path){
	for (size_t i = 0; i < path.size(); ++i) {
		if (path[i] == '/')
			return true;
	}
	return false;
}

void	printVector(std::vector<std::string> vec) {
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << std::endl;
	}
}

bool	IsAbsolutePath(std::string path) {
	if (path[0] == '/')
		return true;
	return false;
}

bool	IsExecutable(std::string path) {
	if (!access(path.c_str(), X_OK)) {
		return false;
	}
	return true;
}

std::string MakeAbsolutePath(std::string executable, std::string path) {
	std::string new_path;
	if (executable[0] == '.' && executable[1] == '/') {
		new_path = path + executable.substr(2, executable.size() - 2);
	}
	else {
		new_path = path + executable;
	}
	return new_path;
}

std::string	GetPWD() {
	PWD pwd;
	return pwd.GetCwd();
}

PWD::PWD() {
	char pwd[MAX_PATH_LIMIT];
	getcwd(pwd, MAX_PATH_LIMIT);
	_cwd = std::string(pwd);
}

std::string PWD::GetCwd() const {
	return _cwd;
}