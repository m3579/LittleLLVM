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

#ifndef SYMBOL_H
#define SYMBOL_H

#include <vector>

#include "Token.hpp"
#include "Node.hpp"
#include "ast.hpp"
#include "SmartPointer.hpp"

using namespace pointer;

namespace parser
{
    class TokenManager;
}

namespace ast
{
    class Symbol
    {
        public:
            Symbol(TokenType tokenType, std::string name, ActionAfterParserEvent actionAfterFind, NodeType nodeType);
            virtual ~Symbol();

            virtual void addNextSymbol(SP<Symbol> nextSymbol, int precedence);

            virtual std::map<SP<ast::Symbol>, int> getNextSymbols();

            TokenType tokenType;

            std::string name;

            ActionAfterParserEvent actionAfterFind;

            NodeType nodeType;

            ActionAfterParserEvent noFind;

            std::vector<SP<ast::Symbol>> possibleNextSymbols;

            std::map<SP<ast::Symbol>, int> precedences;

    };

} /* namespace ast */

#endif // TERMINAL_H
