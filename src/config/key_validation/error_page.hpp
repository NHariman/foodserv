// https://nginx.org/en/docs/http/ngx_http_core_module.html#error_page

// first put everything in vectors
// then make the last value in the vector the uri
// then validate if all values before that one are numbers
// then create a map that takes a std::string in the first bit and a vector<int>
// in the second bit
// probably need a vector of maps like this tbh
// because you can assign multiple error page types