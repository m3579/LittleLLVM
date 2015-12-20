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
#include "SmartPointer.hpp"

using namespace pointer;

namespace parser
{
    extern bool exit;

    class Parser
    {
        public:
            Parser(lexer::Lexer lexr);
            virtual ~Parser();

            virtual SP<ast::SyntaxTree> createSyntaxTree();

            virtual void addSymbol(SP<ast::Symbol> symbol);

            ast::AstManipulationAction noFind;

            std::map<SP<ast::Symbol>, int> precedences;

        protected:
            SP<ast::Branchable> lookFor(SP<ast::Symbol> lookingFor, TokenManager& tm);

            bool tryToFindSymbol(SP<ast::Symbol> symbol, SP<ast::Branchable> root, parser::TokenManager& tm, std::map<SP<ast::Symbol>, int> precedences);

            lexer::Lexer lexr;

            std::vector<SP<ast::Symbol>> symbols;
    };

} /* namespace parser */

#endif // PARSER_H
