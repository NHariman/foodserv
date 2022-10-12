#include "cgi.hpp"

#define DEBUG 0

// SETS HEADERS
void 		CGI::SetHeaders() {

	if (!_request->GetQuery().empty() && !_request->GetMethod().compare("POST")) {
			_env.push_back("CONTENT_LENGTH=" + std::to_string(_request->GetQuery().size()));
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

// identifies where the CGI is located and builds an absolute path towards it
// behaviour changes depending on locationURI (directory or not) and amount of arguments
// in the cgi_pass directive.
void		CGI::SetArgv() {
	if (_CGI.GetLen() == 1) {
		SetCGIOneArgument();
	}
	else
		SetCGITwoArguments();
}

void 		CGI::ToArgv(char **argv){
	argv[0] = strdup(_argv[0].c_str());
	if (_CGI.GetLen() == 2)
		argv[1] = strdup(_argv[1].c_str());
	else
		argv[1] = NULL;
	argv[2] = NULL;
}
void 		CGI::ToEnv(char **env){
	for (size_t i = 0; i < _env.size(); ++i) {
		env[i] = strdup(_env[i].c_str());
	}
}



#undef DEBUG