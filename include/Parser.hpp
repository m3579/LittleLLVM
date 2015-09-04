/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#include "SyntaxTree.hpp"
#include "Lexer.hpp"
#include "Terminal.hpp"
#include "TokenManager.hpp"
#include "../NodeType.h"

using namespace ast;
using namespace lexer;

namespace parser
{
    extern bool exit;

    class Parser
    {
        public:
            Parser(Lexer lexr);
            ~Parser();

            SyntaxTree createSyntaxTree();

            void addTerminal(Terminal& terminal);

            // Return whether or not the terminal was found
            bool assembleTerminal(Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm);

            astAction noFind;

        private:
            Lexer lexr;

            std::vector<Terminal*> terminals;
    };

} /* namespace parser */

#endif // PARSER_H
