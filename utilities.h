#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 15, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

// TODO: organize includes (alphabetical order, remove unnecessary ones, etc.) in all files
#include <iostream>
#include <string>
#include <fstream>

#define iterate_over(iter, list) auto iter = list.begin(); iter != list.end(); ++iter

namespace utilities
{
    // TODO: have some form of outputs

    void logError(std::string message);
}


#endif // UTILITIES_HPP_INCLUDED
