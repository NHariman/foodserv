#include "cgi.hpp"

# define DEBUG 0
# define POST_TEST 0

# define POST_STRING "python=yes"

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

	if (!IsAbsolutePath(_CGI.GetExecutablePath()) && _TARGET.GetLocationUri().IsDir() == true && IsDirectory(_request->GetTargetURI().GetParsedURI()) == true) {
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

bool	CGI::IsExecutable(std::string path) {
	if (!access(path.c_str(), X_OK)) {
		_status_code = 403;
		_valid_file = false;
		return false;
	}
	return true;
}

// identifies where the CGI is located and builds an absolute path towards it
// behaviour changes depending on locationURI (directory or not) and amount of arguments
// in the cgi_pass directive.
void		CGI::SetArgv() {
	std::string executable_path = GetExecutablePath();
	_file_name = executable_path;
	if (IsExecutable(_file_name) == false)
		return ;
	_argv.push_back(executable_path);
	if (_CGI.GetLen() > 1 && _valid_file == true) {
		std::string file;

		if(_TARGET.GetLocationUri().IsDir() == true && IsDirectory(_request->GetTargetURI().GetParsedURI()) == true) {
			// if location match & request target URI is a directory, find file in said directory
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
					if (DEBUG) file = "not real";
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

	if (POST_TEST == 1) {
			std::string str(POST_STRING);
			_env.push_back("CONTENT_LENGTH=" + std::to_string(str.size()));
	}
	else if (!_request->GetTargetURI().GetQuery().empty() && !_request->GetMethod().compare("POST")) {
			_env.push_back("CONTENT_LENGTH=" + std::to_string(_request->GetTargetURI().GetQuery().size()));
	}
	if (_request->GetField("Content-Type").compare(NO_VAL) != 0)
		_env.push_back("CONTENT_TYPE=" + 	_request->GetField("CONTENT_TYPE"));
	_env.push_back("DOCUMENT_ROOT=" + 	_TARGET.GetRoot());
	if (_CGI.GetLen() == 1)
		_env.push_back("PATH_INFO=" + _argv[0]);
	else
		_env.push_back("PATH_INFO=" + _argv[1]);
	if (!_request->GetTargetURI().GetQuery().empty() && _request->GetMethod().compare("GET") == 0)
		_env.push_back("QUERY_STRING=" + 	_request->GetTargetURI().GetQuery());
	if (_request->GetField("HOST").compare(NO_VAL) != 0)
		_env.push_back("REMOTE_HOST=" + 	_request->GetField("HOST"));
	if (!_request->GetMethod().empty())
		_env.push_back("REQUEST_METHOD=" + 	_request->GetMethod());
	_env.push_back("SCRIPT_FILENAME=" + _file_name);
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
void		CGI::ChildProcess(int *fd_read, int *fd_write) {
	char * argv[3];
	char* env[15];
	memset(argv, 0, 3);
	memset(env, 0, 15);
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
	
	if (_request->GetMethod().compare("POST") == 0) { // for POST
		dup2(fd_write[0], STDIN_FILENO);
	}
	if (fd_read[1] != STDOUT_FILENO) {
		dup2(fd_read[1], STDOUT_FILENO);
	}
	if (_request->GetMethod().compare("POST") == 0) // POST
		close(fd_write[1]);
	close(fd_read[0]);
	execve(argv[0], argv, env);
	exit(1);

}

void		CGI::RetrieveContent(int *fd_read){
 
	int count;
	char buffer[1001];
	if (memset(buffer, 0, 1001) == NULL)
		MemsetFailureException();
	while ((count = read(fd_read[0], buffer, 1000)) > 0) {
		if (count == 0)
			break ;
		std::string buf(buffer);
		_content = _content + buf;
		memset(buffer, 0, 1001);
	}
	if (count == -1) {
			close (fd_read[0]);
			throw ReadFailureException();
	}
	return ;
}

void		CGI::WriteToPipe(int fd) {
	if (POST_TEST == 0)
		write(fd, _request->GetTargetURI().GetQuery().c_str(), _request->GetTargetURI().GetQuery().size());
	else {
		std::string str(POST_STRING);
		write(fd, str.c_str(), str.size());
	}
}

int			CGI::ParentProcess(int *fd_read, int *fd_write, int pid) {
	int es = 0;
	int status = 0;

	if (_request->GetMethod().compare("POST") == 0)
		close(fd_write[0]);
	close(fd_read[1]);
	if (_request->GetMethod().compare("POST") == 0)
		WriteToPipe(fd_write[1]);
	if (waitpid(pid, &status, WNOHANG) == -1)
		throw WaitFailureException();
	if (WIFEXITED(status)) {
		es = WEXITSTATUS(status);
	}
	RetrieveContent(fd_read);
	return es;
}




size_t		CGI::execute() {
	int fd_write[2];
	int fd_read[2];
	int pid;
	int exit_code = 0;

	if (pipe(fd_read) < 0 || pipe(fd_write) < 0)
		throw PipeFailureException();
	if (_request->GetMethod().compare("POST") != 0) {
		close (fd_write[0]);
		close(fd_write[1]);
	}
	pid = fork();
	if (pid < 0)
		throw ForkFailureException();
	else if (pid == 0) {
		ChildProcess(fd_read, fd_write);
	}
	else {
		exit_code = ParentProcess(fd_read, fd_write, pid);
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
#undef POST_TEST