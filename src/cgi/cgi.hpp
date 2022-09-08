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
    _env.push_back("QUERY_STRING=" + request->GetField("QUERY_STRING"));
    _env.push_back("REDIRECT_STATUS=" + request->GetField("REDIRECT_STATUS"));
    _env.push_back("REMOTE_ADDR=" + request->GetField("REMOTE_ADDR"));
    _env.push_back("REMOTE_HOST=" + request->GetField("REMOTE_HOST"));
    _env.push_back("REQUEST_METHOD=" + request->GetField("REQUEST_METHOD"));
    _env.push_back("SCRIPT_FILENAME=" + request->GetField("SCRIPT_FILENAME"));
    _env.push_back("SCRIPT_NAME=" + request->GetField("SCRIPT_NAME"));
    _env.push_back("SERVER_NAME=" + request->GetField("SERVER_NAME"));
    _env.push_back("SERVER_PORT=" + request->GetField("SERVER_PORT"));
    _env.push_back("SERVER_PROTOCOL=" + request->GetField("SERVER_PROTOCOL"));
    _env.push_back("SERVER_SOFTWARE=" + request->GetField("SERVER_SOFTWARE"));
}

/*
const char** argv = new const char*[ arg.size() ];
for(size_t a=0; a<arg.size(); ++a) argv[a] = arg[a].c_str();
execv(... argv ...);
// cleanup when error happened
delete[] argv;
*/