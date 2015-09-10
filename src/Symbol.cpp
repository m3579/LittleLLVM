/*
 * Symbol.cpp
 *
 * /TheCompilerFramework/Sources/src/Symbol.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose: Represents a Symbol in the source code. See Parser.cpp/hpp for more information.
 *               Each Symbol contains a list of Symbols that are the next possible Symbols in
 *               the statement.
 *
 *        Usage: Will be created by the user and given to the Parser. The Parser will use Symbols
 *               to find matches in the source code for different types of statements.
 *
 *        Notes:
 *
 */

#include <iostream>

#include "Symbol.hpp"

namespace ast
{
    Symbol::Symbol(int tokenType, std::string id, astAction actionAfterFind) :
        actionAfterFind(actionAfterFind), id(id), tokenType(tokenType)
    {

    }

    Symbol::~Symbol()
    {

    }

    Symbol Symbol::addNextSymbol(Symbol& nextSymbol)
    {
        nextSymbols.push_back(&nextSymbol);
        return nextSymbol;
    }

    int Symbol::getTokenType()
    {
        return tokenType;
    }

    std::vector<Symbol*> Symbol::getNextSymbols()
    {
        return nextSymbols;
    }

} /* namespace ast */
