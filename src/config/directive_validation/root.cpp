#include "root.hpp"

Root::Root(std::string input) {
    if (input.compare("") == 0)
        throw MissingArgumentsException();
}