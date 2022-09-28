#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

#include "cgi.hpp"

class CGIHandler {
    private:
        CGI _cgi;
        size_t  _status_code;
    public:
        CGIHandler();
        CGIHandler(Request *request);
        ~CGIHandler(){};
        std::string GetContent() const;
}

#endif