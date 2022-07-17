#include "autoindex.hpp"

Autoindex::Autoindex(std::string value) {
    if (value.compare("on") != 0 && value.compare("off") != 0)
        throw InvalidAutoindexException();
    if (value.compare("on"))
        _status = true;
    else if (value.compare("off"))
        _status = false;
}

bool     Autoindex::GetStatus() const {
    return _status;
}