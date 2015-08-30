/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
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
    Terminal::Terminal(Token token, afterFind actionAfterFind, int nodeType) :
        actionAfterFind(actionAfterFind), nodeType(nodeType), token(token)
    {

    }

    Terminal::~Terminal()
    {

    }

    Terminal Terminal::addTerminal(Terminal nextTerminal)
    {
        nextTerminals.push_back(nextTerminal);
        return nextTerminal;
    }

    Token Terminal::getToken()
    {
        return token;
    }

    std::vector<Terminal> Terminal::getNextTerminals()
    {
        return nextTerminals;
    }

} /* namespace ast */
