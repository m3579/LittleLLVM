/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>

namespace parser
{

    class Parser
    {
        public:
            Parser(std::string sourceCode);
            ~Parser();

        private:
            std::string sourceCode;
    };

} /* namespace parser */

#endif // PARSER_H
