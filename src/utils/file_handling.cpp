#include <fcntl.h> // creat
#include <sys/stat.h> // stat
#include <iostream>
#include <fstream> // fstream
#include <sstream> // stringstream
#include <string> // to_string
#include <unistd.h> // close

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

// Creates a file. Optional argument `close_after` defaults to false.
// If set to true, closes file fd before returning.
int CreateFile(std::string const& file_path, bool close_after) {
	// equivalent to open with O_CREAT | O_WRONLY | O_TRUNC,
	// with user read/write and group/other read permissions.
    int fd = creat(file_path.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
	if (fd < 0)
		return -1;
	if (close_after)
		close(fd);
	return fd;
}

std::string	GetLastModified(std::string const& path) {
	struct stat sb;

	if (stat(path.c_str(), &sb) != 0)
		return "";

	char	buf[100];
	struct tm	tm = *gmtime(&sb.st_mtime);
	strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", &tm);

	return std::string(buf);
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
	std::fstream* stream = new std::fstream(file_path);
	if (!stream->is_open() || !stream->good())
		return NULL;
	return stream;
}
