#include "cgi.hpp"

# define DEBUG 0

/*
** variables in this class:
** 		Request *_request;
** 		std::vector<std::string> _env;
** 		std::vector<std::string> _argv;

** 		bool		_valid_file;
** 		std::string	_file_name;
** 		std::string _content;
** 		std::string _path;
*/


CGI::CGI() : _valid_file(false) {};

// the most important function, returns true if setup was a success and false if it was a failure
// set argv handles the file sorting and such
bool		CGI::Setup(Request *request) {
	PWD pwd;
	_request = request;
	_path = pwd.GetCwd() + _TARGET.GetResolvedPath();
	if (DEBUG) std::cout << "path: " << _path << std::endl;
	if (DEBUG) std::cout << "CGI: " << _CGI << std::endl;
	SetArgv();
	if (_valid_file == true) {
		SetHeaders();
	}
	if (DEBUG) printVector(_argv);
	if (DEBUG) printVector(_env);
	if (DEBUG) std::cout << "_valid_file " << std::boolalpha << _valid_file << std::endl;
	return (_valid_file);
}

void	CGI::SetExecStatusCode(int exit_code) {
	if (exit_code > 0 || exit_code < 0)
		throw BadGatewayException();
}

size_t		CGI::Execute() {
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
		SetExecStatusCode(exit_code);
	}
	return 200;
}

std::string CGI::GetContent() const {
	return _content;
}

#undef DEBUG