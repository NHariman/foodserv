#include "cgi.hpp"

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
	SetArgv();
	if (_valid_file == true) {
		SetHeaders();
	}
	std::cout << "print vector _env:" << std::endl;
	PrintVector(_env);
	std::cout << "print vector _argv:" << std::endl;
	PrintVector(_argv);
	std::cout << "_valid_file: " << std::boolalpha << _valid_file << std::endl;
	return (_valid_file);
}

void	CGI::SetExecStatusCode(int exit_code) {
	if (exit_code > 0 || exit_code < 0)
		throw BadGatewayException();
}

// actually executes the cgi and saves its contents for returning to the CGIHandler class
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
	std::cout << "print content\n: " << _content << std::endl;
	return 200;
}

std::string CGI::GetContent() const {
	return _content;
}
