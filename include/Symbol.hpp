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
    typedef void (*astAction)(parser::TokenManager&);

    class Symbol
    {
        public:
            Symbol(TokenType tokenType, std::string name, astAction actionAfterFind, NodeType nodeType);
            virtual ~Symbol();

            virtual Symbol addNextSymbol(Symbol& nextSymbol, int precedence);

            virtual std::map<Symbol*, int> getNextSymbols();

            TokenType tokenType;

            NodeType nodeType;

            astAction actionAfterFind;

            astAction noFind;

            std::string name;

            int precedence;

        protected:
            std::map<Symbol*, int> nextSymbolPrecedences;
    };

} /* namespace ast */

#endif // TERMINAL_H
