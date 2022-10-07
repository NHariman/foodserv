#ifndef CGI_HPP
# define CGI_HPP

#include <string>
#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>

#include "../config/directive_validation/cgi_pass.hpp"
#include "../resolved_target/target_config.hpp"
#include "../request/request.hpp"
#include "../utils/utils.hpp"
#include "../utils/cgi_utils.hpp"
#include "../err/sys_exceptions.hpp"

#include <vector>

// https://github.com/klange/cgiserver/blob/master/cgiserver.c

/*
HOW TO CGI:
- set environment
- find file with the correct extension within the path, correct extension can be found in CGIPass with GetExtension();
- set up pipes so you can execute it and read from stdout
- needs request fd
- execute it with the path to the executable necessary to compile and execute the file with, found in CGIPass with GetExecutablePath();
- if a dud path is given, error 404.
- catch what's been written to stdout and save it in a buffer to return in response.
*/

/*
https://stackoverflow.com/questions/28921089/i-have-written-my-own-http-server-and-i-want-to-execute-a-cgi-script-through-thi
*/

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

/* CGI logic:
	- if 2 arguments: use 2nd argument to execute file
	- if 1 argument: consider it an executable and try to execute it
*/


# define _CGI _request->GetTargetConfig().GetCGIPass()
# define _TARGET _request->GetTargetConfig()

class CGI {
	private:
		PWD		_pwd;
		Request *_request;
		std::vector<std::string> _env;
		std::vector<std::string> _argv;

		bool		_valid_file;
		std::string	_file_name;
		std::string _content;
		std::string _path;
		size_t		_status_code;

		// in cgi.cpp
		void	SetExecStatusCode(int exit_code);

		// in cgi_argv_env.cpp
		void    SetHeaders();
		void	SetArgv();
		void 	ToArgv(char **argv);
		void 	ToEnv(char **env);

		// in cgi_pathfinder.cpp
		std::string SetExecutablePath();
		std::string FindFile();
		void		SetCGIOneArgument();
		void		SetCGITwoArguments();

		// in cgi_parent_child.cpp
		void	ChildProcess(int *fd_read, int *fd_write);
		int		ParentProcess(int *fd_read, int *fd_write, int pid);
		void	WriteToPipe(int fd);
		void	RetrieveContent(int *fd_read);

		// in cgi_validation.cpp
		bool		FileLocationCompare(std::string file_one, std::string file_two);
		bool		FileNameCompare(std::string file_one, std::string file_two);
		bool		ValidateExtension(std::string *file);
		bool		HasExtension(std::string file_name);
		bool		ValidScript(std::string executable_path);
		bool		IsExecutable(std::string path);
		bool		IsValidPath(std::string executable_path);
		std::string	RemoveQuery(std::string path);

	public:
		CGI();
		~CGI(){};
		// in cgi.cpp
		bool    	Setup(Request *request); // also probably needs the request class to set ENVs with.
		size_t    	Execute();
		std::string	GetFileName() const;
		std::string GetContent() const;
		size_t		GetStatusCode() const;

};

#endif