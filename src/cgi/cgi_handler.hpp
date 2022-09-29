#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

#include "cgi.hpp"
#include "../response/response.hpp"

class CGIHandler {
    private:
        CGI _cgi;
        size_t  _status_code;
    public:
        CGIHandler();
        ~CGIHandler(){};
        void  execute(Request *request, Response *response);
        std::string GetContent() const;
};

#endif