/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server_block.hpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:35:37 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/07 21:00:13 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BLOCK_HPP
# define SERVER_BLOCK_HPP
#include <iostream>
#include <map>
#include "location_block.hpp"
#include <vector>
#include <string>
#include <stdexcept>

class ServerBlock {
	private:
		struct s_components
		{
			int		location_block;
			bool	listen;
			bool	server_name;
			bool	root;
			bool	index;
			bool	client_max_body_size;
			bool	error_page;
		}	_check_list; // check list of found keywords in serverblock

		std::vector<LocationBlock>	_location_blocks;
		std::string					_listen; // SANNE: CHANGE FUNCTION TYPE TO VECTOR OF YOUR LISTEN CLASS
		std::string					_server_name; // SANNE: FUNCTION TYPE TO VECTOR OF YOUR SERVER_NAME CLASS
		std::string					_root;
		std::string					_index;
		int							_client_max_body_size;
		std::map<int, std::string>	_error_page;

		int							IsKey(std::string key);
		int							SetValue(int key, std::string value);
		std::string					TrimValue(std::string value);
		void						CheckListVerification();
		
	public:
		ServerBlock(std::ifstream &file, size_t *start); // uses a pointer so it can skip through the server bits on its own when it returns
		ServerBlock();
		ServerBlock(const ServerBlock &server_block);
		ServerBlock & operator= (const ServerBlock &server_block);
		~ServerBlock(){};
		
		size_t						FindKeyValuePairs(size_t *start_position, std::string config_file);
		std::vector<LocationBlock>	GetLocationBlocks() const;
		std::string					GetListen() const; // SANNE: CHANGE FUNCTION TYPE TO VECTOR OF YOUR LISTEN CLASS
		std::string					GetServerName() const; // SANNE: CHANGE FUNCTION TYPE TO VECTOR OF YOUR SERVER_NAME CLASS
		std::string					GetRoot() const;
		std::string					GetIndex() const;
		int							GetClientMaxBodySize() const;
		std::map<int, std::string>	GetErrorPage() const;

		// exception classes
		class InvalidKeyException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Invalid Key detected.";
				}
		};
		class MultipleListensException : public std::exception
		{
			public:
				const char *what() const throw() {
					return "ERROR! Multiple listen keys detected.";
				}
		};

};

#endif