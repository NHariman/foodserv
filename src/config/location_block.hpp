
#ifndef LOCATION_BLOCK_HPP
# define LOCATION_BLOCK_HPP

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "../utils.hpp"

// Coplien form:

// class A final
// {
//    public:
//       A ();
//       A (const A &a);
//       ~A ();
//       A & operator = (const A &a);
// };

// if duplicate root is found, throw error


//string trimming util for serverblocks and location blocks


class LocationBlock {
	private:
		struct s_components
		{
			bool	uri;
			bool	autoindex;
			bool	root;
			bool	index;
			bool	client_max_body_size;
			bool	error_page;
			bool	proxy_pass;
			bool	allowed_methods;
		}	_check_list; // check list of found keywords in locationblock
		std::string					_uri;
		bool						_autoindex;
		std::string					_root;
		std::string					_index;
		int							_client_max_body_size;
		std::string					_error_page;
		std::string					_proxy_pass;
		std::string					_allowed_methods;
		LocationBlock(){};
		void						GetKeyValuePairs(std::string data);
		int							IsKey(std::string key);
		void						SetValue(int key, std::string value);
		void						CheckListVerification();

		// input validation
		void						SetUri(std::string uri);

	public:
		LocationBlock(std::string data);
		~LocationBlock(){};
		LocationBlock& operator= (const LocationBlock& location_block);
		LocationBlock(const LocationBlock& location_block);

		// getters
		std::string					GetUri() const;
		bool						GetAutoindex() const;
		std::string					GetRoot() const;
		std::string					GetIndex() const;
		int							GetClientMaxBodySize() const;
		std::string					GetProxyPass() const;
		std::string					GetErrorPage() const;
		std::string					GetAllowedMethods() const;

		// exception classes
		class InvalidKeyException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid Key detected in LocationBlock.";
				}
		};
		class MultipleAutoindexException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple autoindex keys detected in Location block.";
				}
		};
		class MultipleRootException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple root keys detected in Location block.";
				}
		};
		class MultipleIndexException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple index keys detected in Location block.";
				}
		};
		class MultipleErrorPageException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple error_page keys detected in Location block.";
				}
		};
		class MultipleProxyPassException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple proxy_pass keys detected in Location block.";
				}
		};
		class MultipleAllowedMethodsException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple allowed_methods keys detected in Location block.";
				}
		};
		class MultipleClientMaxBodySizeException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple Client_max_body_size keys detected in Location block.";
				}
		};
		class BadURIException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid URI detected in Location block.";
				}
		};
};

#endif