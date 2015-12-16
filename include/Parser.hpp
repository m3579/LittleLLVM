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

#include "Branchable.hpp"
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
            virtual ~Parser();

            virtual ast::SyntaxTree createSyntaxTree();

            virtual void addSymbol(ast::Symbol& symbol);

            // Add the symbol to the syntax tree
            // Return whether or not the symbol was found
            virtual bool tryToFindSymbol(ast::Symbol symbol, ast::Branchable* root, NodeType nodeType, parser::TokenManager& tm);

            ast::astAction noFind;

        protected:
            lexer::Lexer lexr;

            std::vector<ast::Symbol*> symbols;
    };

} /* namespace parser */

#endif // PARSER_H
