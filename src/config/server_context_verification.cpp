#include "server_context.hpp"

#define DEBUG 0

// check if is set
bool						ServerContext::IsSet(std::string directive) {
	int	is_directive = GetDirective(directive);
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveSetCheckException(_server_nb, directive);
	switch (is_directive) {
		case 0:
			return _amount_location_context;
		case 1:
			return bool_listen;
		case 2:
			return bool_server_name;
		case 3:
			return bool_root;
		case 4:
			return bool_index;
		case 5:
			return bool_client_max_body_size;
		case 6:
			return bool_error_page;
		case 7:
			return bool_autoindex;
		case 8:
			return bool_return_dir;
	}
	throw InvalidDirectiveException(directive, _server_nb);
}

int         ServerContext::GetDirective(std::string directive) {
 	const std::string	directives[] = {"location", "listen", "server_name", "root", "index", "client_max_body_size", "error_page", "autoindex", "return"};

    int	is_directive = std::find(directives, directives + 9, directive) - directives;
    return is_directive;
}

// compares found directive with possible directive values and either returns the number in the list
// or throws an error because a bad directive has been found
int			ServerContext::IsDirective(std::string directive){
	int	is_directive = GetDirective(directive);
	if (is_directive < 0 || is_directive > 8)
		throw InvalidDirectiveException(directive, _server_nb);
	else
		return (is_directive);
}

bool					ServerContext::HasLocation(std::string target) {
	for (size_t loc = 0 ; loc < _location_contexts.size() ; loc++) {
		if (target.compare(_location_contexts.at(loc).GetLocationUri().GetUri()) == 0) {
			return true;
		}
	}
	return false;
}

#undef DEBUG