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

#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>

#include "Token.h"
#include "TokenManager.h"
#include "Node.h"

using namespace token;
using namespace node;

namespace parser
{
    TokenManager::TokenManager(std::vector<Token> tokens) :
        tokens(tokens), currentTokenIndex(0), currentToken(tokens.at(currentTokenIndex))
    {

    }

    TokenManager::~TokenManager()
    {

    }

    Token TokenManager::getCurrentToken()
    {
        return currentToken;
    }

    Token TokenManager::fetchNextToken()
    {
        return lookAhead(1);
    }

    Token TokenManager::fetchPreviousToken()
    {
        return lookBehind(1);
    }

    Token TokenManager::lookAhead(int spaces)
    {
        if (currentTokenIndex + spaces < tokens.size()) {
            return tokens.at(currentTokenIndex + spaces);
        }

        return tokens.back();
    }

    Token TokenManager::lookBehind(int spaces)
    {
        if (currentTokenIndex - spaces > 0) {
            return tokens.at(currentTokenIndex - spaces);
        }

        return tokens.front();
    }

    Token TokenManager::moveToNextToken()
    {
        if (currentTokenIndex + 1 < tokens.size()) {
            if (counting) {
                places++;
            }

            return (currentToken = tokens.at(++currentTokenIndex));
        }

        return tokens.back();
    }

    Token TokenManager::moveToPreviousToken()
    {
        if (currentTokenIndex - 1 > 0) {
            if (counting) {
                places--;
            }
            return (currentToken = tokens.at(--currentTokenIndex));
        }

        return tokens.front();
    }

    void TokenManager::startCounting()
    {
        counting = true;
        places = 0;
    }

    int TokenManager::stopCounting()
    {
        counting = false;
        return places;
    }

    void TokenManager::reset()
    {
        if (places > 0) {
            for (int i = 0; i < places; i++) {
                moveToPreviousToken();
            }
        }

        else if (places < 0) {
            for (int i = 0; i > places; i--) {
                moveToNextToken();
            }
        }

        stopCounting();
    }

    bool TokenManager::found(int type)
    {
        if (getCurrentToken().getType() == type) {
            return true;
        }
        return false;
    }

    void TokenManager::consume(int type)
    {
        //
        // When you call consume, you move TO that token, not PAST that token.
        // This is so that if you do something like this (which is done after almost every token in the parser):
        //
        // tm.consume(TokenType::XXX);
        // tm.moveToNextToken();
        //
        // whether or not a token of type XXX is there, you end up on the token after the whitespace/the previous token
        //

        if (fetchNextToken().getType() == type) {
            moveToNextToken();      // move to token
        }
    }

} /* namespace parser */
