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

#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>

#include "Token.hpp"
#include "Node.hpp"

namespace parser
{
    class TokenManager;
}

namespace ast
{
    typedef node::Node (*astAction)(parser::TokenManager&);

    class Symbol
    {
        public:
            Symbol(int tokenType, std::string id, astAction actionAfterFind);
            virtual ~Symbol();

            virtual Symbol addNextSymbol(Symbol& nextSymbol);

            virtual int getTokenType();

            virtual std::vector<Symbol*> getNextSymbols();

            astAction actionAfterFind;

            astAction noFind;

            std::string id;

        protected:
            int tokenType;

            std::vector<Symbol*> nextSymbols;
    };

} /* namespace ast */

#endif // TERMINAL_H
