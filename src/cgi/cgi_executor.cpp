#include "cgi.hpp"

void    execute_cgi(Request *request) {
    CGI cgi;

    if (cgi.setup(request) == false) {
        // set request status code to 404
        return ;
    }
    // request status is equal to status of cgi.execute?


}