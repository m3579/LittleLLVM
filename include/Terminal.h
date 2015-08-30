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

namespace ast
{
    typedef void (*afterFind)(Token);

    class Terminal
    {
        public:
            Terminal(Token token, afterFind actionAfterFind, int nodeType);
            ~Terminal();

            Terminal addTerminal(Terminal nextTerminal);

            Token getToken();

            std::vector<Terminal> getNextTerminals();

            afterFind actionAfterFind;

            int nodeType;

        private:
            Token token;

            std::vector<Terminal> nextTerminals;
    };

} /* namespace ast */

#endif // TERMINAL_H
