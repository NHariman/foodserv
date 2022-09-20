#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <fcntl.h> // open

class FileHandler {
	public:
		FileHandler();
		~FileHandler();

		std::string	GetFileContents(std::string const& file_path);
		std::string	GetExtension(std::string const& file_path) const;
	
	private:
		int	SetToNonBlock(int fd);
};

#endif /* FILE_HANDLER_HPP */
