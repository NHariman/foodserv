/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FindBlocks.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/29 16:23:08 by nhariman      #+#    #+#                 */
/*   Updated: 2022/06/29 16:26:25 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// is called when a block start is found and grabs everything in between
// the curly brackets.
#ifndef FINDBLOCKS_HPP
# define FINDBLOCKS_HPP
#include <string>

class FindBlock{
    private:
        size_t      brackets;
        std::string content;
        FindBlock();
    public:
        FindBlock(std::ifstream& file, size_t start);
        ~FindBlock();
};

#endif