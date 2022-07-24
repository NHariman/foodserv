#include "root.hpp"

Root::Root(std::string input) {
    if (input.compare("") == 0)
        throw MissingArgumentsException();
    size_t  arguments = CountArguments(input);
    if (arguments != 1)
        throw TooManyArgumentsException();
}