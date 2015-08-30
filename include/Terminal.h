/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
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

#include "Token.h"

using namespace token;

namespace parser
{
    class TokenManager;
}

namespace ast
{
    typedef void (*afterFind)(parser::TokenManager&);

    class Terminal
    {
        public:
            Terminal(int tokenType, afterFind actionAfterFind, int nodeType);
            ~Terminal();

            Terminal addTerminal(Terminal& nextTerminal);

            int getTokenType();
            int getNodeType();

            std::vector<Terminal> getNextTerminals();

            afterFind actionAfterFind;

        private:
            int tokenType;
            int nodeType;

            std::vector<Terminal> nextTerminals;
    };

} /* namespace ast */

#endif // TERMINAL_H
