#include "cgi.hpp"

# define DEBUG 1

// script name:
// if only 1 argument in cgi_pass, it's that
// if there are 2 arguments in cgi_pass, need to find the extension title.

/*
* Set CGI environment variables.
* CONTENT_LENGTH    : POST message length
* CONTENT_TYPE      : POST encoding type
* DOCUMENT_ROOT     : the root directory
* GATEWAY_INTERFACE : The CGI version (CGI/1.1)
* HTTP_COOKIE       : Cookies provided by client
* HTTP_HOST         : Same as above
* HTTP_REFERER      : Referer page.
* HTTP_USER_AGENT   : Browser user agent
* PATH_TRANSLATED   : On-disk file path
* QUERY_STRING      : /file.ext?this_stuff&here
* REDIRECT_STATUS   : HTTP status of CGI redirection (PHP)
* REMOTE_ADDR       : IP of remote user
* REMOTE_HOST       : Hostname of remote user (reverse DNS)
* REQUEST_METHOD    : GET, POST, HEAD, etc.
* SCRIPT_FILENAME   : Same as PATH_TRANSLATED (PHP, primarily)
* SCRIPT_NAME       : Request file path
* SERVER_NAME       : Our hostname or Host: header
* SERVER_PORT       : TCP host port
* SERVER_PROTOCOL   : The HTTP version of the request
* SERVER_SOFTWARE   : Our application name and version
*/

bool	IsPath(std::string path){
	for (size_t i = 0; i < path.size(); ++i) {
		if (path[i] == '/')
			return true;
	}
	return false;
}

void CGI::SetHeaders() {
	_env.push_back("CONTENT_LENGTH=" + 	_request->GetField("CONTENT_LENGTH"));
	_env.push_back("CONTENT_TYPE=" + 	_request->GetField("CONTENT_TYPE"));
	_env.push_back("DOCUMENT_ROOT=" + 	_request->GetTargetConfig().GetRoot());
	_env.push_back("HTTP_COOKIE=" + 	_request->GetField("HTTP_COOKIE"));
	_env.push_back("HTTP_HOST=" + 		_request->GetField("HTTP_HOST"));
	_env.push_back("HTTP_REFERER=" + 	_request->GetField("HTTP_REFERER"));
	_env.push_back("HTTP_USER_AGENT=" + _request->GetField("HTTP_USER_AGENT"));
	_env.push_back("PATH_TRANSLATED=" + _target->GetResolvedPath());
	_env.push_back("QUERY_STRING=" + 	_request->GetTargetURI().GetQuery());
	_env.push_back("REDIRECT_STATUS=" + _request->GetField("REDIRECT_STATUS"));
	_env.push_back("REMOTE_ADDR=" + 	_request->GetField("REMOTE_ADDR"));
	_env.push_back("REMOTE_HOST=" + 	_request->GetField("HOST"));
	_env.push_back("REQUEST_METHOD=" + 	_request->GetMethod());
	_env.push_back("SCRIPT_FILENAME=" + _request->GetTargetURI().GetPath());
	_env.push_back("SCRIPT_NAME=" + 	_file_name);
	_env.push_back("SERVER_NAME=" + 	_request->GetTargetURI().GetHost());
	_env.push_back("SERVER_PORT=" + 	_request->GetTargetURI().GetPort());
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("SERVER_SOFTWARE=foodserv");
	

}

bool		CGI::HasExtension(std::string file_name) {
	size_t i = file_name.size() - 1;
	size_t j = _cgi_data.GetFileExtension().size() - 1;

	while (j > 0 && i > 0) {
		if (file_name[i] == _cgi_data.GetFileExtension().at(j)) {
			i--;
			j--;
		}
		else
			break ;
	}
	if (j == 0)
		return true;
	return false;
}

std::string	CGI::FindFile() {
	//open directory listed in resolved path
	// search for first file with extension
	// append file name to resolved path
	// return resolved path file name combo
	

	
	struct dirent *files;
	std::string		file;
	if (IsDirectory(_path) == true) {
		DIR *dr = opendir(_path.c_str());
		if (dr == NULL) {
			_valid_file = false;
			return "";
		}
		while ((files = readdir(dr)) != NULL) {
			if (DEBUG) std::cout << "file name: " << files->d_name << std::endl;
			if (HasExtension(files->d_name)) {
				_file_name = files->d_name;
				file = _path + files->d_name;
				_valid_file = true;
				break ;
			}
		}
		closedir(dr);
	}
	else
		_valid_file = false;
	return (file);
}

void	CGI::SetArgv() {
	std::vector<std::string> argv;
	if (_cgi_data.GetLen() == 1) {
		// check if / are in path, if no, append ./
		// actually probably append the resolved path dir to it.
		// or temporarily move into this dir to execute it?
		// just be sure to move back to the og dir after
		if (IsValidFile(_cgi_data.GetExecutablePath()) == false) {
			_valid_file = false;
			return ;
		}
		_argv.push_back(_cgi_data.GetExecutablePath());
	}
	else {
		_argv.push_back(_cgi_data.GetExecutablePath());
		std::string file = FindFile();
		if (_valid_file == false)
			return ;
		if (DEBUG) std::cout << "Identified executable path: " << file << std::endl;
		_argv.push_back(file);
	}
	_valid_file = true;

}

// check if request is a directory!!
// if it's a directory, find the file with the extension
// if it's not a directory they have to list the cgi explicitly to use it
bool	CGI::setup(Request *request) {
	_cgi_data = request->GetTargetConfig().GetCGIPass();
	_request = request;
	_target = &request->GetTargetConfig();
	_valid_file = false;
	if (DEBUG) std::cout << "amount of arguments: " << _cgi_data.GetLen() << std::endl;
	char c_dir[256];
   	getcwd(c_dir, 256);

	std::string current_dir(c_dir);
    if (DEBUG) cout << "Current working directory: " << c_dir << endl;
	_path = current_dir + _target->GetResolvedPath();
	if (DEBUG) std::cout << "resolved path after adding pwd: " << _path << std::endl;
	SetArgv();
	if (_valid_file == true)
		SetHeaders();
	return (_valid_file);
}

void CGI::to_argv(const char **argv) {
	argv[0] = _argv[0].c_str();
	if (_cgi_data.GetLen() == 2)
		argv[1] = _argv[1].c_str();
	else
		argv[1] = "\0";
	argv[2] = "\0";
}

void CGI::to_env(const char **env) {
	for (size_t i = 0; i < _env.size(); ++i) {
		env[i] = _env[i].c_str();
	}
	env[_env.size()] = "\0";
}

void	CGI::ChildProcess(int *fd, int *tmp_fd) {

	const char* argv[3];
	const char* env[20];
	to_argv(argv);
	to_env(env);
	dup2(*tmp_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(*tmp_fd);
	if (execve(argv[0], (char **)argv, (char **)env) == -1) {
		if (DEBUG) {
			std::cerr << "execve did not execute:" << std::endl;
			std::cerr << "_argv[0]: " << _argv[0] << std::endl;
			std::cerr << "_argv[1]: " << _argv[1] << std::endl;
		}

	}
}

int		CGI::ParentProcess(int *fd, int *tmp_fd, int pid) {
	int es = 0;
	char buffer[1001];
	int status = 0;

	close(*tmp_fd);
	close(fd[1]);
	if (waitpid(pid, &status, 0) == -1)
		throw WaitFailureException();
	if (WIFEXITED(status)) {
		es = WEXITSTATUS(status);
	}
	while (read(fd[0], buffer, 1000) != 0) {
		_content.append(buffer);
		memset(buffer, 0, 1001);
		if (DEBUG) std::cout << "content in buffer: " << _content << std::endl;
	}
	*tmp_fd = dup(fd[0]);
	close(fd[0]);

	return es;
}

// _argv[0] = argv[0].c_str();
// 	if (_cgi_data.GetLen() == 2)
// 		_argv[1] = argv[1].c_str();
// 	else
// 		_argv[1] = NULL;
// 	_argv[2] = NULL;



		// const char * _env[20];
		// const char * _argv[3];

size_t    CGI::execute() {

	int fd[2];
	int pid;
	int exit_status = 0;
	int tmp_fd = dup(STDIN_FILENO);


	if(DEBUG) std::cout << "_argv[0]: " << _argv[0] << std::endl;
	if(DEBUG) std::cout << "_argv[1]: " << _argv[1] << std::endl;

	if (pipe(fd) != 0) {
		throw PipeFailureException();
	}
	pid = fork();	
	if (pid < 0) {
		throw ForkFailureException();
	}
	else if (pid == 0) {
		ChildProcess(fd, &tmp_fd);
	}
	else {
		exit_status = ParentProcess(fd, &tmp_fd, pid);
	}
	close(tmp_fd);
	return exit_status;
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