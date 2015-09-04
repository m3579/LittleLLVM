/*
 * Terminal.cpp
 *
 * /Project/Sources/src/Terminal.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose: Represents a Terminal in the source code. See Parser.cpp/hpp for more information.
 *               Each Terminal contains a list of Terminals that are the next possible Terminals in
 *               the statement.
 *
 *        Usage: Will be created by the user and given to the Parser. The Parser will use Terminals
 *               to find matches in the source code for different types of statements.
 *
 *        Notes:
 *
 */

#include <iostream>

#include "Terminal.h"

namespace ast
{
    Terminal::Terminal(int tokenType, std::string id, astAction actionAfterFind) :
        actionAfterFind(actionAfterFind), id(id), tokenType(tokenType)
    {

    }

    Terminal::~Terminal()
    {

    }

    Terminal Terminal::addNextTerminal(Terminal& nextTerminal)
    {
        nextTerminals.push_back(&nextTerminal);
        return nextTerminal;
    }

    int Terminal::getTokenType()
    {
        return tokenType;
    }

    std::vector<Terminal*> Terminal::getNextTerminals()
    {
        return nextTerminals;
    }

} /* namespace ast */
