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
#include "Node.h"

using namespace token;

namespace parser
{
    class TokenManager;
}

namespace ast
{
    typedef node::Node (*afterFind)(parser::TokenManager&);

    class Terminal
    {
        public:
            Terminal(int tokenType, afterFind actionAfterFind);
            ~Terminal();

            Terminal addTerminal(Terminal& nextTerminal);

            int getTokenType();

            std::vector<Terminal> getNextTerminals();

            afterFind actionAfterFind;

        private:
            int tokenType;

            std::vector<Terminal> nextTerminals;
    };

} /* namespace ast */

#endif // TERMINAL_H
