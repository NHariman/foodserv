#include "client_max_body_size.hpp"
#include <climits>



ClientMaxBodySize::ClientMaxBodySize(std::string value) {
    size_t i = 0;
    size_t found_m = 0;
    size_t    tmp_value;

    if (value.compare("") == 0)
        throw MissingArgumentsException();
    while (value[i]) {
        if (std::isdigit(value[i]) == 0 && value[i] != 'm' && value[i] != 'M')
            throw InvalidClientMaxBodySizeException();
        if (std::isdigit(value[i]) == 1 && found_m == 1)
            throw InvalidClientMaxBodySizeException();
        else if (value[i] == 'm' || value[i] == 'M') {
            if (found_m == 1)
                throw InvalidClientMaxBodySizeException();
            found_m = 1;
        }
        i++;
    }
    tmp_value = ft_atosize_t(value.substr(0, i));
    if (tmp_value < 0)
        throw NegativeClientMaxBodySizeException();
    if (tmp_value > 2147483647)
        throw TooLargeClientMaxBodySizeException();
    _value = tmp_value;
}

int PrintValue(std::string value) {
    size_t i = 0;
    size_t found_m = 0;
    long    _value;

    while (value[i]) {
        if (std::isdigit(value[i]) == 0 && value[i] != 'm' && value[i] != 'M')
            return -1;
        if (std::isdigit(value[i]) == 1 && found_m == 1)
            return -1;
        else if (value[i] == 'm' || value[i] == 'M') {
            if (found_m == 1)
                return -1;
            found_m = 1;
        }
        i++;
    }
    _value = ft_atosize_t(value.substr(0, i));
    return (_value);
}

size_t ClientMaxBodySize::GetValue() const {
    return _value;
}