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

#include <iostream>
#include <stdexcept>
#include <fstream>

#include "utilities.h"

namespace utilities
{
    // TODO: make it so that you can switch between console and file
    // output in the same program
    std::streambuf* outputDebugsToFile(std::string filename)
    {
        std::filebuf file;
        file.open(filename, std::ios::out);
        std::streambuf* normalSTDOUT = std::cout.rdbuf(&file);
        std::cout << "To file\n";
        return normalSTDOUT;
    }

    void logError(std::string message)
    {
        throw std::runtime_error("Error in LittleLLVM compiler: " + message);
    }
}
