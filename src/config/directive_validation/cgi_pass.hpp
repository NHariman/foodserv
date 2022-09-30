#ifndef CGI_PASS_HPP
# define CGI_PASS_HPP

#include <string>
#include <iostream>
#include "../../utils/config_utils.hpp"
#include "../../request/uri.hpp"
#include "../../utils/cgi_utils.hpp"

class CGIPass : public std::pair<std::string, std::string> {
	private:
        bool        						_is_set;
		size_t								_len;
		std::string							_file_extension;
		std::string							_executable_path;

	public:
		CGIPass();
		CGIPass(std::string input);
		~CGIPass(){};
        CGIPass(CGIPass const &obj);
        CGIPass& operator=(const CGIPass &obj);
		std::string		GetFileExtension() const;
		std::string		GetExecutablePath() const;
		size_t			GetLen() const;
        bool            IsSet() const;
		class MissingArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Missing Arguments in cgi_pass directive.";
				}
		};
		class TooManyArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Too many Arguments in cgi_pass directive.";
				}
		};
		class NotEnoughArgumentsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Not enough Arguments in cgi_pass directive.";
				}
		};
		class NotAFileExtensionException : public std::exception
		{
			private:
				std::string _err_msg;
			public:
				NotAFileExtensionException(std::string extension) {
					_err_msg = "ERROR! cgi_pass directive failure: " + extension + " is not a file extension (extension must begin with a '.')";
				}
				const char *what() const throw() {
					return (_err_msg.c_str());
				}
                virtual ~NotAFileExtensionException() throw() {}
		};
		class NotAPathException : public std::exception
		{
			private:
				std::string _err_msg;
			public:
				NotAPathException(std::string _executable_path) {
					_err_msg = "ERROR! cgi_pass directive failure: " + _executable_path + " is not a file path (path must be a relative path or absolute path)";
				}
				const char *what() const throw() {
					return (_err_msg.c_str());
				}
                virtual ~NotAPathException() throw() {}
		};
};

std::ostream& operator<<(std::ostream& os, const CGIPass& cgi_pass);

#endif