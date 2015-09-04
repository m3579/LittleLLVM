/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 28, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <string>

#include "Parser_test.hpp"

#define VERSION 1.0

void help(const char* topic);

int main(int argc, const char* argv[])
{
    // Skip over first arg (program name)
    argv++;
    argc--;

    if (argc == 0) {

        std::string topic;

        std::cout << "The Compiler Framework\n"
                  << "A framework for writing compiler front-ends in C++\n"
                  << "Version " << VERSION << "\n\n"
                  << "Enter a topic to get help on it: ";

        getline(std::cin, topic);

        help(topic.c_str());

    }

    else if (argc == 1) {
        help(argv[0]);
    }

    else {
        std::cout << "Unrecognized command\n\n"
                  << "Use the following:\n"
                  << "\tmycompiler [topic]\n\n";
    }
}

void help(const char* topic)
{
    std::cout << topic << "\n";
}
