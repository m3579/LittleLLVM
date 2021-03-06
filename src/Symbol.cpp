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
    Symbol::Symbol(TokenType tokenType, std::string name, std::function<void(parser::TokenManager&)> actionAfterFind, NodeType nodeType) :
        tokenType(tokenType), name(name), actionAfterFind(actionAfterFind), nodeType(nodeType)
    {

    }

    Symbol::~Symbol()
    {

    }

    void Symbol::addNextSymbol(SP<ast::Symbol> nextSymbol, int precedence)
    {
        possibleNextSymbols.push_back(nextSymbol);
        precedences[nextSymbol] = precedence;
    }

    std::map<SP<Symbol>, int> Symbol::getNextSymbols()
    {
        return precedences;
    }

} /* namespace ast */
