#include "cgi.hpp"

#include <fcntl.h>

# define DEBUG 0
# define POST_TEST 0

# define POST_STRING "python=yes"


// set processes
void		CGI::ChildProcess(int *fd_read, int *fd_write) {
	char * argv[3];
	char* env[15];
	memset(argv, 0, 3);
	memset(env, 0, 15);
	to_argv(argv);
	to_env(env);

	// if (DEBUG) {
	// 	std::cout << "print char* argv:" << std::endl;
	// 	int i = 0;
	// 	while (argv[i] != NULL) {
	// 		std::cout << argv[i] << std::endl;
	// 		i++;
	// 	}
	// 	i = 0;
	// 	std::cout << "print char* env:" << std::endl;
	// 	while (env[i] != NULL) {
	// 		std::cout << env[i] << std::endl;
	// 		i++;
	// 	}
	// }
	
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

void		CGI::WriteToPipe(int fd) {
	if (POST_TEST == 0)
		write(fd, _request->GetTargetURI().GetQuery().c_str(), _request->GetTargetURI().GetQuery().size());
	else {
		std::string str(POST_STRING);
		write(fd, str.c_str(), str.size());
	}
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

#undef DEBUG
#undef POST_TEST
#undef POST_STRING