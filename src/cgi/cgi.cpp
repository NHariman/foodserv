#include "cgi.hpp"

# define DEBUG 0

/*
** variables in this class:
**		PWD		_pwd;
** 		Request *_request;
** 		std::vector<std::string> _env;
** 		std::vector<std::string> _argv;

** 		bool		_valid_file;
** 		std::string	_file_name;
** 		std::string _content;
** 		std::string _path;
*/


CGI::CGI() : _pwd(), _valid_file(false) {};

// the most important function, returns true if setup was a success and false if it was a failure
// set argv handles the file sorting and such
bool		CGI::setup(Request *request) {
	_request = request;
	_path = _pwd.GetCwd() + _TARGET.GetResolvedPath();
	if (DEBUG) std::cout << "path: " << _path << std::endl;
	SetArgv();
	if (_valid_file == true)
		SetHeaders();
	if (DEBUG) printVector(_argv);
	if (DEBUG) printVector(_env);
	return (_valid_file);
}

bool		CGI::HasExtension(std::string file_name) {
	size_t i = file_name.size() - 1;
	size_t j = _CGI.GetFileExtension().size() - 1;

	while (j > 0 && i > 0) {
		if (file_name[i] == _CGI.GetFileExtension().at(j)) {
			j--;
			i--;
		}
		else
			break ;
	}
	if (j == 0)
		return true;
	return false;
}

std::string CGI::FindFile() {
	struct dirent *directory;
	std::string file;
	DIR *dr = opendir(_path.c_str());
	if (dr == NULL) {
		_valid_file = false;
		return "";
	}
	while ((directory = readdir(dr)) != NULL) {
		if (HasExtension(directory->d_name)) {
			_file_name = directory->d_name;
			file = _path + directory->d_name;
			_valid_file = true;
			break ;
		}
		_valid_file = false;
	}
	closedir(dr);
	return (file);
}

std::string CGI::GetExecutablePath() {
	std::string executable_path;

	if (!IsAbsolutePath(_CGI.GetExecutablePath()) && _TARGET.GetLocationUri().IsDir() == true) {
		executable_path = MakeAbsolutePath(_CGI.GetExecutablePath(), _path);
	}
	else if (!IsAbsolutePath(_CGI.GetExecutablePath())) {
		executable_path = _path;
	}
	else {
		executable_path = _CGI.GetExecutablePath();
	}
	if (IsValidFile(executable_path) || IsValidDirectory(executable_path))
		_valid_file = true;
	if (DEBUG) std::cout << "executable_path: " << executable_path << std::endl;
	return (executable_path);
}

// identifies where the CGI is located and builds an absolute path towards it
// behaviour changes depending on locationURI (directory or not) and amount of arguments
// in the cgi_pass directive.
void		CGI::SetArgv() {
	std::string executable_path = GetExecutablePath();
	_file_name = executable_path;
	_argv.push_back(executable_path);
	if (_CGI.GetLen() > 1 && _valid_file == true) {
		std::string file;

		if(_TARGET.GetLocationUri().IsDir() == true && IsDirectory(_request->GetTargetURI().GetParsedURI()) == true) {
			// if location match & request target URI is a directory, find file in said directory
			std::cout << "where am i?" << std::endl;
			file = FindFile();
		}
		else {
			// assumes the locationURI is the cgi file
			// checks if extension of the location URI matches
			// the allowed cgi_pass extension
			if (HasExtension(_path) == true) {
				file = _path;
				_valid_file = true;
			}
			else {
				if (IsValidFile(_path)) {
					file = _path;
					_valid_file = true;
				}
				else{
					file = "not real";
					_valid_file = false;
				}
			}
		}
		if (DEBUG) std::cout << "file: " << file << std::endl;
		_file_name = file;
		_argv.push_back(file);
	}
	if (DEBUG) std::cout << "valid file check: " << std::boolalpha << _valid_file << std::endl;
}

void 		CGI::SetHeaders() {
	if (_request->GetField("Content-Length").compare(NO_VAL) != 0)
		_env.push_back("CONTENT_LENGTH=" + 	_request->GetField("Content-Length"));
	if (_request->GetField("Content-Type").compare(NO_VAL) != 0)
		_env.push_back("CONTENT_TYPE=" + 	_request->GetField("Content-Type"));
	_env.push_back("DOCUMENT_ROOT=" + 	_TARGET.GetRoot());
	_env.push_back("PATH_TRANSLATED=" + _TARGET.GetResolvedPath());
	if (!_request->GetTargetURI().GetQuery().empty())
		_env.push_back("QUERY_STRING=" + 	_request->GetTargetURI().GetQuery());
	if (_request->GetField("HOST").compare(NO_VAL) != 0)
		_env.push_back("REMOTE_HOST=" + 	_request->GetField("HOST"));
	if (!_request->GetMethod().empty())
		_env.push_back("REQUEST_METHOD=" + 	_request->GetMethod());
	_env.push_back("SCRIPT_FILENAME=" + _request->GetTargetURI().GetPath());
	_env.push_back("SCRIPT_NAME=" + 	_file_name);
	_env.push_back("SERVER_NAME=" + 	_request->GetTargetURI().GetHost());
	_env.push_back("SERVER_PORT=" + 	_request->GetTargetURI().GetPort()); // ask sanne for fix?
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("SERVER_SOFTWARE=foodserv");
}

void 		CGI::to_argv(char **argv){
	argv[0] = strdup(_argv[0].c_str());
	if (_CGI.GetLen() == 2)
		argv[1] = strdup(_argv[1].c_str());
	else
		argv[1] = NULL;
	argv[2] = NULL;
}
void 		CGI::to_env(char **env){
	for (size_t i = 0; i < _env.size(); ++i) {
		env[i] = strdup(_env[i].c_str());
	}
}

// set processes
void		CGI::ChildProcess(int *fd) {
	char * argv[3];
	char* env[20];
	memset(argv, 0, 3);
	memset(env, 0, 20);
	to_argv(argv);
	to_env(env);

	if (DEBUG) {
		std::cout << "print char* argv:" << std::endl;
		int i = 0;
		while (argv[i] != NULL) {
			std::cout << argv[i] << std::endl;
			i++;
		}
		i = 0;
		std::cout << "print char* env:" << std::endl;
		while (env[i] != NULL) {
			std::cout << env[i] << std::endl;
			i++;
		}
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	execve(argv[0], argv, env);
	exit(1);

}

int			CGI::ParentProcess(int *fd, int pid) {
	int es = 0;
	char buffer[1001];
	int status = 0;
	ssize_t count = 1;

	close(fd[1]);
	if (waitpid(pid, &status, WNOHANG) == -1)
		throw WaitFailureException();
	if (WIFEXITED(status)) {
		es = WEXITSTATUS(status);
	}
	while ((count = read(fd[0], buffer, sizeof(buffer))) > 0) {
		std::string buf(buffer);
		_content = _content + buf;
		memset(buffer, 0, 1001);
	}
	close(fd[0]);
	if (count == -1) {
			throw ReadFailureException();
	}
	return es;
}




size_t		CGI::execute() {
	int fd[2];
	int pid;
	int exit_code = 0;

	if (pipe(fd) < 0)
		throw PipeFailureException();
	pid = fork();
	if (pid < 0)
		throw ForkFailureException();
	else if (pid == 0) {
		ChildProcess(fd);
	}
	else {
		exit_code = ParentProcess(fd, pid);
	}
	return exit_code;
}


bool		CGI::isValidFile() const {
	return _valid_file;
}
std::string	CGI::getFileName() const {
	return _file_name;
}
std::string CGI::getContent() const {
	return _content;
}

#undef DEBUG