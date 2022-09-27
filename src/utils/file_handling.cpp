#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>

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

// Takes a string to open as a stringstream object (which inherits from iostream),
// and returns a pointer to the heap-allocated object.
std::istream*	CreateStreamFromString(std::string const& string_buffer) {
	std::istream* stream = new std::stringstream(string_buffer);
	return stream;
}

// Takes a file path to open as a fstream object (which inherits from iostream),
// and returns a pointer to the heap-allocated object.
// Returns NULL if file opening fails.
std::istream*	CreateStreamFromPath(std::string const& file_path) {
	std::ifstream* stream = new std::ifstream(file_path);
	if (!stream->is_open() || !stream->good())
		return NULL;
	return stream;
}
