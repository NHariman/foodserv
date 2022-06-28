/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   LocationBlock.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 20:49:39 by nhariman      #+#    #+#                 */
/*   Updated: 2022/06/28 17:15:32 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONBLOCK_HPP
# define LOCATIONBLOCK_HPP

#include <iostream>
#include <map>

class LocationBlock {
	private:
		std::string					uri;
		bool						autoindex;
		std::string					root;
		std::vector<std::string>	index;
		int							client_max_body_size;
		std::map<int, std::string>	error_page;
		LocationBlock(){};
	public:
		LocationBlock(std::ifstream &file, size_t *start); // uses a pointer so it can skip through the server bits on its own when it returns
		~LocationBlock(){};
};

#endif