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

using namespace token;

namespace parser
{
    class TokenManager;

    typedef bool (TokenManager::*isXxx) (Token);

    class TokenManager
    {
        public:
            TokenManager(std::vector<Token>);
            ~TokenManager();

            // The methods that take a string an a bool as arguments
            // have the capability to log an error (the string is the message, the bool
            // whether or not it is fatal)

            Token getCurrentToken();
            Token fetchNextToken();
            Token fetchPreviousToken();
            Token lookAhead(int);
            Token lookBehind(int);
            Token moveToNextToken();
            Token moveToPreviousToken();

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
            std::vector<Token> tokens;

            unsigned int currentTokenIndex;

            Token currentToken;

            bool counting;
            int places;

    };

}

#endif // TOKENMANAGER_H_
