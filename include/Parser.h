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

#include "SyntaxTree.h"
#include "Lexer.h"

using namespace ast;
using namespace lexer;

namespace parser
{
    class Parser
    {
        public:
            Parser(std::string sourceCode, Lexer lexr);
            ~Parser();

            SyntaxTree createSyntaxTree();

        private:
            std::string sourceCode;

            Lexer lexr;

    };

} /* namespace parser */

#endif // PARSER_H
