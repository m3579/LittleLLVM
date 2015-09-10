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
#include "Symbol.hpp"
#include "TokenManager.hpp"
#include "../NodeType.h"

namespace parser
{
    extern bool exit;

    class Parser
    {
        public:
            Parser(lexer::Lexer lexr);
            ~Parser();

            ast::SyntaxTree createSyntaxTree();

            void addSymbol(ast::Symbol& terminal);

            // Return whether or not the terminal was found
            bool assembleSymbol(ast::Symbol terminal, ast::SyntaxTree& syntaxTree, parser::TokenManager& tm);

            ast::astAction noFind;

        private:
            lexer::Lexer lexr;

            std::vector<ast::Symbol*> terminals;
    };

} /* namespace parser */

#endif // PARSER_H
