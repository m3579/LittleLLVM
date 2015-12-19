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

namespace parser
{
    class TokenManager;
}

namespace ast
{
    class Symbol
    {
        public:
            Symbol(TokenType tokenType, std::string name, std::function<void(parser::TokenManager&)> actionAfterFind, NodeType nodeType);
            virtual ~Symbol();

            virtual void addNextSymbol(std::shared_ptr<Symbol> nextSymbol, int precedence);

            virtual std::map<std::shared_ptr<ast::Symbol>, int> getNextSymbols();

            TokenType tokenType;

            std::string name;

            std::function<void(parser::TokenManager&)> actionAfterFind;

            NodeType nodeType;

            std::function<void(parser::TokenManager&)> noFind;

            std::vector<std::shared_ptr<ast::Symbol>> possibleNextSymbols;

            std::map<std::shared_ptr<ast::Symbol>, int> precedences;

    };

} /* namespace ast */

#endif // TERMINAL_H
