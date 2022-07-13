/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_string.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 18:19:53 by nhariman      #+#    #+#                 */
/*   Updated: 2022/04/16 21:10:43 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "print_string.hpp"
#include <iostream>


std::string     print_string(std::string str, std::string add)
{
    std::string newstr;
    newstr = str + add;
    return newstr;
}

int             addition(int a, int b)
{
    return a + b;
}
