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
            virtual ~TokenManager();

            // The methods that take a string an a bool as arguments
            // have the capability to log an error (the string is the message, the bool
            // whether or not it is fatal)

            virtual token::Token getCurrentToken();
            virtual token::Token fetchNextToken();
            virtual token::Token fetchPreviousToken();
            virtual token::Token lookAhead(int);
            virtual token::Token lookBehind(int);
            virtual token::Token moveToNextToken();
            virtual token::Token moveToPreviousToken();

            // Start counting how many tokens have been read since the current token at the time
            // of method call
            virtual void startCounting();
            // Stop counting and return number of tokens
            virtual int stopCounting();
            // move back to token that was current token when startCounting was called
            virtual void reset();

            virtual bool found(TokenType);

            virtual void consume(TokenType);

            virtual bool hasMoreTokens();

        protected:
            std::vector<token::Token> tokens;

            unsigned int currentTokenIndex;

            token::Token currentToken;

            bool counting;
            int places;

    };

}

#endif // TOKENMANAGER_H_
