#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <iostream>
#include <cerrno> // erno

class FileHandler {
	public:
		FileHandler();
		~FileHandler();

		std::istream*	GetFile(std::string const& file_path);
		std::istream*	CreateFile(std::string const& file_path);
		std::string		GetExtension(std::string const& file_path) const;
	
	private:
		void	GetFileHandlingError(void);
};

#endif /* FILE_HANDLER_HPP */
