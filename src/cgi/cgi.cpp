#include "cgi.hpp"

void CGI::SetHeaders(Request *request) {
	_env.push_back("CONTENT_LENGTH=" + request->GetField("CONTENT_LENGTH"));
	_env.push_back("CONTENT_TYPE=" + request->GetField("CONTENT_TYPE"));
	_env.push_back("DOCUMENT_ROOT=" + request->GetField("DOCUMENT_ROOT"));
	_env.push_back("HTTP_COOKIE=" + request->GetField("HTTP_COOKIE"));
	_env.push_back("HTTP_HOST=" + request->GetField("HTTP_HOST"));
	_env.push_back("HTTP_REFERER=" + request->GetField("HTTP_REFERER"));
	_env.push_back("HTTP_USER_AGENT=" + request->GetField("HTTP_USER_AGENT"));
	_env.push_back("PATH_TRANSLATED=" + request->GetField("PATH_TRANSLATED"));
	_env.push_back("QUERY_STRING=" + request->GetTargetURI().GetQuery());
	_env.push_back("REDIRECT_STATUS=" + request->GetField("REDIRECT_STATUS"));
	_env.push_back("REMOTE_ADDR=" + request->GetField("REMOTE_ADDR"));
	_env.push_back("REMOTE_HOST=" + request->GetField("HOST"));
	_env.push_back("REQUEST_METHOD=" + request->GetField("REQUEST_METHOD"));
	_env.push_back("SCRIPT_FILENAME=" + request->GetField("SCRIPT_FILENAME"));
	_env.push_back("SCRIPT_NAME=" + request->GetField("SCRIPT_NAME"));
	_env.push_back("SERVER_NAME=" + request->GetField("SERVER_NAME"));
	_env.push_back("SERVER_PORT=" + request->GetField("SERVER_PORT"));
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("SERVER_SOFTWARE=foodserv");
}



void	CGI::setup(CGIPass *cgi_data, Request *request) {
	_cgi_data = *cgi_data;
	SetHeaders(request);
	SetArgv(request);
}

size_t    CGI::execute() {
	vtoa env(_env);
	vtoa argv(_argv);

	int fd[2];
	int pid;
	int status;
	int tmp_fd = dup(STDIN_FILENO);
	if (pipe(fd) != 0) {
		throw PipeFailureException();
	}
	pid = fork();
	if (pid < 0) {
		throw ForkFailureException();
	}
	else if (pid == 0) {
		dup2(tmp_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		close(tmp_fd);
		execve(_cgi_data.GetExecutablePath().c_str(), argv.GetArray(), env.GetArray());
		exit(404);
	}
	else {
		close(tmp_fd);
		close(fd[1]);
		if (waitpid(pid, &status, 0) == -1)
			throw WaitFailureException();
		tmp_fd = dup(fd[0]);
		close(fd[0]);
		if (WIFEXITED(status)) {
			const int es = WEXITSTATUS(status);
			if (es == 404)
				return es;
		}
	}
	close(tmp_fd);
	return 0;
}