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

#include <string>

#define iterate_over(iter, list) auto iter = list.begin(); iter != list.end(); ++iter

namespace utilities
{
    extern bool showDebugStatements;

    std::streambuf* outputDebugsToFile(std::string filename);

    void logError(std::string message);
}


#endif // UTILITIES_HPP_INCLUDED
