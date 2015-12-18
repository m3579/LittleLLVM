/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 17, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <stdexcept>

#include "utilities.h"

namespace utilities
{
    void logError(std::string message)
    {
        throw std::runtime_error("Error in LittleLLVM compiler: " + message);
    }
}
