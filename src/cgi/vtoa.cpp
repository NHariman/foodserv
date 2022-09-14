#include "vtoa.hpp"

vtoa::vtoa(std::vector<std::string> vec) {
    _array = new const char*[vec.size()];
    for (size_t i = 0; i < vec.size(); ++i) {
        _array[i] = vec[i].c_str();
    }
}

 char *const * vtoa::GetArray() const {
    return (char *const *)_array;
}

vtoa::~vtoa() {
    delete [] _array;
}

/*
const char** argv = new const char*[ arg.size() ];
for(size_t a=0; a<arg.size(); ++a) argv[a] = arg[a].c_str();
execv(... argv ...);
// cleanup when error happened
delete[] argv;
*/