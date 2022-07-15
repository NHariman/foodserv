#include <iostream>
#include <stdexcept>

class ClientMaxBodySize {
    private:
        int     _value;

        ClientMaxBodySize(){};
    
    public:
        ClientMaxBodySize(std::string value);
        int     GetClientMaxBodySize() const;

        class InvalidClientMaxBodySizeException : public std::exception
        {
            public:
                const char *what() const throw() {
                    return "ERROR! Invalid client_max_body_size in location block.";
                }
        };   
};