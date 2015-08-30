/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
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
#include "Terminal.h"
#include "TokenManager.h"

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

            // Return whether or not the terminal was found
            bool assembleTerminal(Node supernode, Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm);

        private:
            std::string sourceCode;

            Lexer lexr;

            std::vector<Terminal> terminals;
    };

} /* namespace parser */

#endif // PARSER_H
