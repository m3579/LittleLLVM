/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
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

#include <iostream>

#include "Terminal.h"

namespace ast
{
    Terminal::Terminal(int tokenType, afterFind actionAfterFind) :
        actionAfterFind(actionAfterFind), tokenType(tokenType)
    {

    }

    Terminal::~Terminal()
    {

    }

    Terminal Terminal::addTerminal(Terminal& nextTerminal)
    {
        nextTerminals.push_back(nextTerminal);
        return nextTerminal;
    }

    int Terminal::getTokenType()
    {
        return tokenType;
    }

    std::vector<Terminal> Terminal::getNextTerminals()
    {
        return nextTerminals;
    }

} /* namespace ast */
