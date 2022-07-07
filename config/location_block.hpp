/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   location_block.hpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:39 by nhariman      #+#    #+#                 */
/*   Updated: 2022/07/07 21:25:43 by nhariman      ########   odam.nl         */
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

class LocationBlock {
	private:
		std::string					_uri;
		bool						_autoindex;
		std::string					_root;
		std::string					_index;
		int							_client_max_body_size;
		std::map<int, std::string>	_error_page;
		LocationBlock(){};
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
		std::map<int, std::string>	GetErrorPage() const;
};

#endif