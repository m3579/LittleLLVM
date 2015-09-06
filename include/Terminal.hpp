/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#include "Token.hpp"
#include "Node.hpp"

namespace parser
{
    class TokenManager;
}

namespace ast
{
    typedef node::Node (*astAction)(parser::TokenManager&);

    class Terminal
    {
        public:
            Terminal(int tokenType, std::string id, astAction actionAfterFind);
            ~Terminal();

            Terminal addNextTerminal(Terminal& nextTerminal);

            int getTokenType();

            std::vector<Terminal*> getNextTerminals();

            astAction actionAfterFind;

            astAction noFind;

            std::string id;

        private:
            int tokenType;

            std::vector<Terminal*> nextTerminals;
    };

} /* namespace ast */

#endif // TERMINAL_H
