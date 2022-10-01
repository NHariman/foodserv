#include "cgi.hpp"

// create cgi handler class intead of this function
void    execute_cgi(Request *request) {
    CGI cgi;

    if (cgi.setup(request) == false) {
       request->SetStatusCode(502);
        return ;
    }
    if (cgi.execute() > 0) {
        request->SetStatusCode(502);
    }
    else {
        request->SetStatusCode(200);
    }
    // request status is equal to status of cgi.execute?
}