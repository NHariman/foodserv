#include "cgi.hpp"

#include <fcntl.h>


// child process executes the cgi
void		CGI::ChildProcess(int *fd_read, int *fd_write) {
	char * argv[3];
	char* env[15];
	if (memset(argv, 0, 3) == NULL)
		throw MemsetFailureException();
	if (memset(env, 0, 15) == NULL)
		throw MemsetFailureException();
	ToArgv(argv);
	ToEnv(env);
	
	if (_request->GetMethod().compare("POST") == 0) { // for POST
		if (dup2(fd_write[0], STDIN_FILENO) == -1)
			throw DupFailureException();
	}
	if (fd_read[1] != STDOUT_FILENO) {
		if (dup2(fd_read[1], STDOUT_FILENO) == -1)
			throw DupFailureException();
	}
	if (_request->GetMethod().compare("POST") == 0) // POST
		close(fd_write[1]);
	close(fd_read[0]);
	execve(argv[0], argv, env);
	exit(1);
}

// FOR POST
// writes query to stdin of the child process
void		CGI::WriteToPipe(int fd) {
	int status = write(fd, _request->GetQuery().c_str(), _request->GetQuery().size());
	if (status == -1 || status != (int)_request->GetQuery().size())
		throw WriteFailureException();
}

// retrieves the content in the stdout of the child
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
		if (memset(buffer, 0, 1001) == NULL)
			throw MemsetFailureException();
	}
	if (count == -1) {
			close (fd_read[0]);
			throw ReadFailureException();
	}
	return ;
}

// parent process reads the stdout of the child process and saves its content
// and in the event of a POST request, also writes to the stdin of the child process
// for the CGI to use
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
    close (fd_read[0]);
	return es;
}
