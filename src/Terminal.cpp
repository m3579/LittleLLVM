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

#include "Terminal.h"

namespace ast
{
    Terminal::Terminal(int tokenType, afterFind actionAfterFind, int nodeType) :
        actionAfterFind(actionAfterFind), tokenType(tokenType), nodeType(nodeType)
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

    int Terminal::getNodeType()
    {
        return nodeType;
    }

    std::vector<Terminal> Terminal::getNextTerminals()
    {
        return nextTerminals;
    }

} /* namespace ast */
