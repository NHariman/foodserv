#include "cgi.hpp"

#include <fcntl.h>

# define DEBUG 0
# define POST_TEST 0

# define POST_STRING "python=yes"


// child process executes the cgi
void		CGI::ChildProcess(int *fd_read, int *fd_write) {
	char * argv[3];
	char* env[15];
	memset(argv, 0, 3);
	memset(env, 0, 15);
	ToArgv(argv);
	ToEnv(env);
	
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

// FOR POST
// writes query to stdin of the child process
void		CGI::WriteToPipe(int fd) {
	ssize_t status;
	if (POST_TEST == 0)
		status = write(fd, _request->GetTargetURI().GetQuery().c_str(), _request->GetTargetURI().GetQuery().size());
	else {
		std::string str(POST_STRING);
		status = write(fd, str.c_str(), str.size());
	}
	if (status == -1)
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
		memset(buffer, 0, 1001);
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

#undef DEBUG
#undef POST_TEST
#undef POST_STRING