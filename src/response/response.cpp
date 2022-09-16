#include "response.hpp"

// Default constructor
Response::Response() : AHTTPMessage(), _complete(false) {}

// Destructor
Response::~Response() {}


std::string const& Response::GetReasonPhrase() const {
    return _reason_phrase;
}

void Response::SetReasonPhrase(std::string const& phrase) {
    _reason_phrase = phrase;
}

bool Response::IsComplete() const {
    return _complete;    
}
