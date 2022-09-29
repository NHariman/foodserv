#include <algorithm> // count
#include <cerrno> // erno
#include <dirent.h> // DIR, dirent
#include "file_handler.hpp"
#include "../utils/utils.hpp"
#include "../err/exception.hpp"

#define DEBUG 1 // TODO: REMOVE

FileHandler::FileHandler() {}

FileHandler::~FileHandler() {}

// Tries to open the file as a stream.
std::istream*	FileHandler::GetFile(std::string const& file_path) {
	if (!IsValidFile(file_path))
		GetFileHandlingError();

	std::istream* file_stream = CreateStreamFromPath(file_path);
	if (file_stream == NULL)
		throw InternalServerErrorException();
	return file_stream;
}

// Returns file extension without '.' or empty string if no extension found.
std::string	FileHandler::GetExtension(std::string const& file_path) const {
	size_t period_pos = file_path.find_last_of('.');

	if (period_pos != std::string::npos)
		return file_path.substr(period_pos + 1);
	return "";
}

void	FileHandler::GetFileHandlingError(void) {
	if (errno == ENOENT)
		throw NotFoundException();
	else if (errno == EACCES)
		throw ForbiddenException();
	else
		throw InternalServerErrorException();
}

std::istream*	FileHandler::ExecuteMethod(Response& response, Method method) {
	switch (method) {
		case Method::Get:
			return ExecuteGet(response);
		case Method::GetError:
			return ExecuteGet(response, true);
		case Method::GetGeneratedIndex:
			return ExecuteGetGeneratedIndex(response);
		case Method::Post:
			return ExecutePost(response);
		case Method::Delete:
			return NULL;
		default:
			return NULL;
	}
}

// Tries to retrieve file. Sets response status code when done
// if not retrieving error page.
std::istream*	FileHandler::ExecuteGet(Response& response, bool error_page) {
	if (DEBUG) std::cout << "ExecuteGet: path: " << response.GetResolvedPath() << std::endl;

    std::istream*	file = GetFile(response.GetResolvedPath());
	if (!error_page)
		response.SetStatusCode(200);
	return file;
}

// Called when index must be served but index file is not found.
std::istream*	FileHandler::ExecuteGetGeneratedIndex(Response& response) {
	if (DEBUG) std::cout << "ExecuteGetGeneratedIndex: path: " << response.GetResolvedPath() << std::endl;

	std::string	resolved_path = response.GetResolvedPath();

	struct dirent*	dir_entry;
	DIR *dir_path = opendir(resolved_path.c_str());
	if (dir_path == NULL)
		throw InternalServerErrorException();

	std::string index_of = "Index of " + GetSubDirForIndex(resolved_path);
	std::string	index = "<html>\r\n<head><title>" + index_of + "</title></head>\r\n"
		+ "<body>\r\n<h1>" + index_of + "</h1><hr>\r\n";

	while ((dir_entry = readdir(dir_path)) != NULL)
		index += FormatLine(dir_entry, resolved_path);
	index += "<hr>\r\n</body>\r\n</html>";
	closedir(dir_path);
	// std::cout<< index << std::endl; // REMOVE
	std::istream* stream = CreateStreamFromString(index);

	response.SetStatusCode(200);
	response.SetHeaderField("Content-Type", "text/html");
	return stream;
}

// Gets subdirectory path for index page.
std::string	FileHandler::GetSubDirForIndex(std::string const& dir_path) {
	if (DEBUG) std::cout << "GetSubDirForIndex\n";

	size_t slash_first = dir_path.find_first_of("/");
	size_t slash_last = dir_path.find_last_of("/");
	if (slash_first == std::string::npos)
		throw InternalServerErrorException();
	
	if (slash_first == slash_last)
		return dir_path.substr(slash_first);
	else
		return dir_path.substr(slash_first, slash_last - slash_first + 1);
}

// Formats readdir returns into html.
std::string	FileHandler::FormatLine(struct dirent* dir_entry, std::string const& path) {
	if (DEBUG) std::cout << "FormatLine\n";
	
	std::string	file_name(dir_entry->d_name);

	// skip prev directory link for security
	if (file_name == ".." || file_name == ".")
		return "";
	// if directory
	else if (dir_entry->d_type == DT_DIR)
		file_name += "/";

	std::string	line = "<a href=\"" + path + file_name + "\">" + file_name + "</a>";
	std::string	last_modified = GetLastModified(path + file_name);

	if (last_modified.empty())
		throw InternalServerErrorException();
	else
		line += " " + last_modified + "\r\n<br>";
	return line;
}

std::string	StripLeadingSlash(std::string const& file_path) {
	if (file_path[0] == '/'){
		std::cout << "Stripped path: " << file_path.substr(1) << std::endl;
		return file_path.substr(1);
	}
	else
		return file_path;
}

// if POST, validate info and create file. File stream/message should have success/failure message.
std::istream*	FileHandler::ExecutePost(Response& response) {
	std::cout << "Executing Post on file: " << response.GetResolvedPath() << "\n";
	bool created = false;
	std::string	file_path = StripLeadingSlash(response.GetResolvedPath());

	if (!ValidSubDirectory(file_path))
		throw ForbiddenException();

	// check if file does not exist yet
	if (!IsValidFile(file_path) && errno == ENOENT) {
		if (CreateFile(file_path) < 0)
			GetFileHandlingError();
		else
			created = true;
	}
	std::cout << "created file at: " << file_path << std::endl;

	// insert request body into file
	std::fstream* file = dynamic_cast<std::fstream*>(CreateStreamFromPath(file_path));
	std::cout << "file size: " << file->gcount() << std::endl;
	// std::cout << "body: " << response.GetMessageBody() << std::endl;
	*file << response.GetMessageBody();
	if (created) {
		response.SetStatusCode(201);
		return CreateStreamFromString("File successfully created\n");
	}
	else {
		response.SetStatusCode(200);
		return NULL;
	}
}

// Grabs directory part of file path.
std::string	GetDirectoryPath(std::string const& file_path) {
	size_t slash_last = file_path.find_last_of("/");
	if (slash_last == std::string::npos)
		return "./";
	return file_path.substr(0, slash_last + 1);
}

// Checks if directory path of request target is valid.
bool	FileHandler::ValidSubDirectory(std::string const& file_path) {
	std::string dir_path = GetDirectoryPath(file_path);
	if (dir_path == "/")
		return true;
	else
		return IsValidDirectory(dir_path);
}

#undef DEBUG // REMOVE
