#ifndef CONFIG_INTERFACE_HPP
# define CONFIG_INTERFACE_HPP

#include "server_context.hpp"
#include "location_context.hpp"
#include "directive_validation/directive_validation.hpp"

class ConfigValues {
    protected:
        bool	bool_root;
	    bool	bool_index;
	    bool	bool_client_max_body_size;
	    bool	bool_error_page;
	    bool	bool_autoindex;
	    bool	bool_return_dir;

        std::string						_root;
		std::vector<std::string>		_index;
		size_t							_client_max_body_size;
		std::vector<ErrorPage>			_error_page;
		bool							_autoindex;
		ReturnDir						_return_dir;
    
	protected:
       virtual void						InitChecklist() = 0;
       virtual int                      IsDirective(std::string directive) = 0;
       virtual void                     GetDirectiveValuePairs(std::string data){ static_cast<void>(data); throw MethodNotSetException("GetDirectiveValuePairs()");}
       virtual void                     SetValue(int directive, std::string value) = 0;
       virtual void                     CheckListVerification() = 0;
	   ConfigValues();
	   ConfigValues(const ConfigValues& obj);
	   ConfigValues&	operator=(const ConfigValues& obj);
	   virtual ~ConfigValues(){};

    public:
       //getters
       virtual std::string					GetRoot() const;
       virtual std::vector<std::string>	    GetIndex() const;
       virtual size_t						GetClientMaxBodySize() const;
       virtual std::vector<ErrorPage>		GetErrorPage() const;
       virtual bool						    GetAutoindex() const;
       virtual ReturnDir                    GetReturn() const;

       virtual bool							HasErrorPage() const;

	   // checks if a directive has been set
       virtual bool							IsSet(std::string directive) = 0;

		// method not set exception
		class MethodNotSetException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MethodNotSetException(std::string method) {
					_err_string = method + " was not declared in derived class from which the method was called.";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};

		// invalid directive exceptions
		class InvalidDirectiveSetCheckException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				InvalidDirectiveSetCheckException(size_t server) {
					_err_string = "Invalid directive detected in Server Context no." + std::to_string(server) + " .";
				}
				InvalidDirectiveSetCheckException(std::string uri) {
					_err_string = "Invalid directive detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
       class InvalidDirectiveException : public std::exception
		{
			public:
				InvalidDirectiveException(std::string directive, size_t server) {
					_err_string = "ERROR! Multiple invalid directive (" + directive + ") in Server Context no." + std::to_string(server) + " .";
				}
                InvalidDirectiveException(std::string uri) {
					_err_string = "ERROR! Invalid directive detected in Location Context:" + uri + ".";
				}
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
		class DirectiveNotSetException : public std::exception
		{
			public:
                DirectiveNotSetException(std::string directive) {
					_err_string = "WARNING! Get attempt failed, directive: " + directive + " was not set.";
				};
				DirectiveNotSetException(std::string directive, size_t server) {
					_err_string = "WARNING! Get attempt failed, directive: " + directive + " was not set in server no." + std::to_string(server) + ".";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};

		// Multiple directives exceptions
        class MultipleRootException : public std::exception
		{
			public:
				MultipleRootException(size_t server) {
					_err_string = "ERROR! Multiple root directives found in Server Context: " + std::to_string(server) + " .";
				}
                MultipleRootException(std::string uri) {
					_err_string = "ERROR! Multiple root directives detected in Location Context:" + uri + ".";
				}
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
        class MultipleIndexException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
                MultipleIndexException(size_t server) {
					_err_string = "ERROR! Multiple index directives found in Server Context: " + std::to_string(server) + " .";
				}
				MultipleIndexException(std::string uri) {
					_err_string = "ERROR! Multiple index directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
        class MultipleClientMaxBodySizeException : public std::exception
		{
			public:
				MultipleClientMaxBodySizeException(size_t server) {
					_err_string = "ERROR! Multiple client_max_body_size directives found in Server Context: " + std::to_string(server) + " .";
				}
                MultipleClientMaxBodySizeException(std::string uri) {
					_err_string = "ERROR! Multiple client_max_body_size directives detected in Location Context:" + uri + ".";
				}
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
			private:
				std::string		_err_string;
		};
        class MultipleErrorPageException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
                MultipleErrorPageException(size_t server) {
					_err_string = "ERROR! Multiple error_page directives detected in Server Context: " + std::to_string(server) + " .";
				}
				MultipleErrorPageException(std::string uri) {
					_err_string = "ERROR! Multiple error_page directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
        class MultipleAutoindexException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleAutoindexException(size_t server) {
					_err_string = "ERROR! Multiple autoindex directives detected in Server Context: " + std::to_string(server) + " .";
				}
                MultipleAutoindexException(std::string uri) {
					_err_string = "ERROR! Multiple autoindex directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
		class MultipleReturnException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleReturnException(size_t server) {
					_err_string = "ERROR! Multiple return directives detected in Server Context: " + std::to_string(server) + " .";
				}
                MultipleReturnException(std::string uri) {
					_err_string = "ERROR! Multiple return directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
		};
};

#endif