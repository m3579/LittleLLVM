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


namespace utilities
{

    void logError(std::string message)
    {
        throw std::runtime_error("Little LLVM - Bug in compiler:\n\t" + message + "\n\n");
    }

}


#endif // UTILITIES_HPP_INCLUDED
