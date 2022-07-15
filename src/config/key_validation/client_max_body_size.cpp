#include "client_max_body_size.hpp"

ClientMaxBodySize::ClientMaxBodySize(std::string value) {
    size_t i = 0;
    size_t found_m = 0;
    int end = value.size();

    // if (value[end] != 'm' && value[end] != 'M' && std::isdigit(value[end]) == 0)
    //     throw InvalidClientMaxBodySizeException();
    while (value[i]) {
        if (std::isdigit(value[i]) == 1)
            i++;
        else if (value[end] == 'm' && value[end] == 'M') {
            if (found_m == 1)
                throw InvalidClientMaxBodySizeException();
            found_m = 1;
            i++;
        }
        else
            throw InvalidClientMaxBodySizeException();
    }
    _value = std::atoi(value.substr(0, i).c_str());
}