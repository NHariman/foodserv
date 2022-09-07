#include <string>
#include <iostream>

#include "../config/directive_validation/cgi_pass.hpp"
#include "../server_selection/target_config.hpp"
#include "../request/request.hpp"

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


class CGI {
    private:
        CGIPass _cgi_data;

    public:
        CGI(){};
        ~CGI(){};
        Setup(CGIPass *cgi_data, Request *request); // also probably needs the request class to set ENVs with.


        
};