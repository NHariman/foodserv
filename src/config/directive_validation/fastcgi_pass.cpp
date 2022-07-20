#include "fastcgi_pass.hpp"

FastCGIPass::FastCGIPass(std::string input) {
    if (input.compare("") == 0)
        throw MissingArgumentsException();
}