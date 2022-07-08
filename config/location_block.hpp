/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_block.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:39 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/08 22:25:40 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_BLOCK_HPP
# define LOCATION_BLOCK_HPP

#include <iostream>
#include <map>
#include <vector>

// Coplien form:

// class A final
// {
//    public:
//       A ();
//       A (const A &a);
//       ~A ();
//       A & operator = (const A &a);
// };

//string trimming util for serverblocks and location blocks
std::string	TrimValue(std::string value);

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
		}	_check_list; // check list of found keywords in locationblock
		std::string					_uri;
		bool						_autoindex;
		std::string					_root;
		std::string					_index;
		int							_client_max_body_size;
		std::string					_error_page;
		std::string					_proxy_pass;
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

		// exception classes
		class InvalidKeyException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid Key detected in LocationBlock.";
				}
		};
};

#endif