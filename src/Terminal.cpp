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
