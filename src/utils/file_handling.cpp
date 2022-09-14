#include <sys/types.h>
#include <sys/stat.h>
#include "utils.hpp"

bool	IsValidFile(std::string const& path) {
	struct stat sb;

	if (stat(path.c_str(), &sb) == 0)
		return true;
	return false;
}

bool	IsValidDirectory(std::string const& path) {
	struct stat sb;

	if (stat(path.c_str(), &sb) == 0) {
		if (S_ISDIR(sb.st_mode))
			return true;
	}
	return false;
}
