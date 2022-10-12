#ifndef CONFIG_EXCEPTIONS_HPP
# define CONFIG_EXCEPTIONS_HPP

#include <stdexcept>

///////////////////////
// SHARED EXCEPTIONS //
///////////////////////

class BadInputException : public std::exception
{
	public:
		BadInputException(size_t server) {
			_err_string = "ERROR! Bad directive input found in server context: " + std::to_string(server) + " .";
		};
		BadInputException(std::string uri) {
			_err_string = "ERROR! Invalid input detected in Location Context:" + uri + ".";
		}
		virtual const char *what() const throw() {
			return _err_string.c_str();
		}
		virtual ~BadInputException() throw() {}
	private:
		std::string		_err_string;
};

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
		virtual ~MethodNotSetException() throw() {}
};

// invalid directive exceptions
class InvalidDirectiveSetCheckException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		InvalidDirectiveSetCheckException(size_t server, std::string directive) {
			_err_string = "Invalid directive detected in Server Context no." + std::to_string(server) + ": " + directive;
		}
		InvalidDirectiveSetCheckException(std::string uri) {
			_err_string = "Invalid directive detected in Location Context:" + uri + ".";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~InvalidDirectiveSetCheckException() throw() {}
};

class InvalidDirectiveException : public std::exception
{
	public:
		InvalidDirectiveException(std::string directive, size_t server) {
			_err_string = "ERROR! Multiple invalid directive (" + directive + ") in Server Context no." + std::to_string(server) + " .";
		}
		InvalidDirectiveException(std::string uri) {
			_err_string = "ERROR! Invalid directive detected in Location Context: " + uri + ".";
		}
        InvalidDirectiveException(std::string uri, std::string directive) {
			_err_string = "ERROR! Invalid directive detected in Location Context: " + uri + "\nDirective: " + directive;
		}
		virtual const char *what() const throw() {
			return _err_string.c_str();
		}
		virtual ~InvalidDirectiveException() throw() {}
	private:
		std::string		_err_string;
};

class DirectiveNotSetException : public std::exception
{
	public:
		DirectiveNotSetException(std::string directive) {
			_err_string = "Directive: " + directive + " not set anywhere.";
		};
		DirectiveNotSetException(std::string directive, std::string host, std::string target) {
			_err_string = "Directive: " + directive + " not set in: " + host + target;
		};
        DirectiveNotSetException(std::string directive, std::string location) {
			_err_string = "ERROR! Get attempt failed, directive: " + directive + " was not set. In Location block: " + location;
		};
		DirectiveNotSetException(std::string directive, size_t server) {
			_err_string = "ERROR! Get attempt failed, directive: " + directive + " was not set in server no." + std::to_string(server) + ".";
		};
		virtual const char *what() const throw() {
			return _err_string.c_str();
		}
		virtual ~DirectiveNotSetException() throw() {}
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
		virtual ~MultipleRootException() throw() {}
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
		virtual ~MultipleIndexException() throw() {}
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
		virtual ~MultipleClientMaxBodySizeException() throw() {}
	private:
		std::string		_err_string;
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
		virtual ~MultipleAutoindexException() throw() {}
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
		virtual ~MultipleReturnException() throw() {}
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
		virtual ~MultipleErrorPageException() throw() {}
};

///////////////////////////////
// SERVER CONTEXT EXCEPTIONS //
///////////////////////////////

class MultipleListensException : public std::exception
		{
			public:
				MultipleListensException(size_t server) {
					_err_string = "ERROR! Multiple listen directives found in server context no. " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
				virtual ~MultipleListensException() throw() {}
			private:
				std::string		_err_string;
		};

class DuplicateLocationUriException : public std::exception
		{
			public:
				DuplicateLocationUriException(size_t server, std::string uri) {
					_err_string = "ERROR! Multiple location uri directives (" + uri + ") found in server context no." + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
				virtual ~DuplicateLocationUriException() throw() {}
			private:
				std::string		_err_string;
		};

class MultipleServerNameException : public std::exception
		{
			public:
				MultipleServerNameException(size_t server) {
					_err_string = "ERROR! Multiple server_names directives found in server context: " + std::to_string(server) + " .";
				};
				virtual const char *what() const throw() {
					return _err_string.c_str();
				}
				virtual ~MultipleServerNameException() throw() {}
			private:
				std::string		_err_string;
		};


/////////////////////////////////
// LOCATION CONTEXT EXCEPTIONS //
/////////////////////////////////

class MultipleCGIPassException : public std::exception
		{
			private:
				std::string		_err_string;
			public:
				MultipleCGIPassException(std::string uri) {
					_err_string = "ERROR! Multiple cgi_pass directives detected in Location Context:" + uri + ".";
				}
				const char *what() const throw() {
					return (_err_string.c_str());
				}
				virtual ~MultipleCGIPassException() throw() {}
		};

class MultipleAllowedMethodsException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		MultipleAllowedMethodsException(std::string uri) {
			_err_string = "ERROR! Multiple allowed_methods directives detected in Location Context:" + uri + ".";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~MultipleAllowedMethodsException() throw() {}
};

class MultipleAliasException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		MultipleAliasException(std::string uri) {
			_err_string = "ERROR! Multiple alias directives detected in Location Context:" + uri + ".";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~MultipleAliasException() throw() {}
};
class BadURIException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		BadURIException(std::string uri) {
			_err_string = "ERROR! Bad URI detected in Location Context:" + uri + ".";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~BadURIException() throw() {}
};

class RootAndAliasException : public std::exception
{
	private:
		std::string		_err_string;
	public:
		RootAndAliasException(std::string uri) {
			_err_string = "ERROR! Location Context:" + uri + " contains both alias and root, please only use one.";
		}
		const char *what() const throw() {
			return (_err_string.c_str());
		}
		virtual ~RootAndAliasException() throw() {}
};

#endif