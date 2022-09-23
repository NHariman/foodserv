#include "cgi.hpp"

void    execute_cgi(Request *request) {
    CGI cgi;

    if (cgi.setup(request) == false) {
       request->SetStatusCode(501);
        return ;
    }
    if (cgi.execute() > 0) {
        request->SetStatusCode(501);
    }
    else {
        request->SetStatusCode(200);
    }
    // convert cgi.getcontent() into filestream here?


}