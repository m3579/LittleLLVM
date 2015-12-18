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

            virtual std::shared_ptr<ast::SyntaxTree> createSyntaxTree();

            virtual void addSymbol(std::shared_ptr<ast::Symbol> symbol);

            // Add the symbol to the syntax tree
            // Return whether or not the symbol was found
            virtual bool tryToFindSymbol(std::shared_ptr<ast::Symbol> symbol, std::shared_ptr<ast::Branchable> root, parser::TokenManager& tm, std::map<std::shared_ptr<ast::Symbol>, int> precedences);

            ast::astAction noFind;

            std::map<std::shared_ptr<ast::Symbol>, int> precedences;

        protected:
            lexer::Lexer lexr;

            std::vector<std::shared_ptr<ast::Symbol>> symbols;
    };

} /* namespace parser */

#endif // PARSER_H
