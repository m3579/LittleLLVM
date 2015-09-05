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
#ifndef TOKENMANAGER_H_
#define TOKENMANAGER_H_

#include <vector>

#include "Token.hpp"
#include "Node.hpp"
#include "../Ref.hpp"

namespace parser
{
    class TokenManager
    {
        public:
            TokenManager(std::vector<token::Token>);
            ~TokenManager();

            // The methods that take a string an a bool as arguments
            // have the capability to log an error (the string is the message, the bool
            // whether or not it is fatal)

            token::Token getCurrentToken();
            token::Token fetchNextToken();
            token::Token fetchPreviousToken();
            token::Token lookAhead(int);
            token::Token lookBehind(int);
            token::Token moveToNextToken();
            token::Token moveToPreviousToken();

            // Start counting how many tokens have been read since the current token at the time
            // of method call
            void startCounting();
            // Stop counting and return number of tokens
            int stopCounting();
            // move back to token that was current token when startCounting was called
            void reset();

            bool found(int);

            void consume(int);

            bool hasMoreTokens();

        private:
            std::vector<token::Token> tokens;

            unsigned int currentTokenIndex;

            token::Token currentToken;

            bool counting;
            int places;

    };

}

#endif // TOKENMANAGER_H_
