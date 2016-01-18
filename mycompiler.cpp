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

#include <iostream>
#include <string>

#define VERSION 1.0

void help(const char* topic);

int main(int argc, const char* argv[])
{
    // Skip over first arg (program name)
    argv++;
    argc--;

    if (argc == 0) {

        std::string topic;

        std::cout << "Little LLVM\n"
                  << "A framework for writing compilers in C++\n"
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
    // TODO implement this
    std::cout << topic << "\n";
}
