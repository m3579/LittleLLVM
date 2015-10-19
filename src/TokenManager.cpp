/*
 * Filename.cpp
 *
 * /TheCompilerFramework/Sources/src/Filename.cpp
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

#include <iostream>

#include "Token.hpp"
#include "TokenManager.hpp"
#include "Node.hpp"
#include "../TokenType.h"

namespace parser
{
    TokenManager::TokenManager(std::vector<token::Token> tokens) :
        tokens(tokens), currentTokenIndex(0), currentToken(tokens.at(currentTokenIndex))
    {

    }

    TokenManager::~TokenManager()
    {

    }

    token::Token TokenManager::getCurrentToken()
    {
        return currentToken;
    }

    token::Token TokenManager::fetchNextToken()
    {
        return lookAhead(1);
    }

    token::Token TokenManager::fetchPreviousToken()
    {
        return lookBehind(1);
    }

    token::Token TokenManager::lookAhead(int spaces)
    {
        if (currentTokenIndex + spaces < tokens.size()) {
            return tokens.at(currentTokenIndex + spaces);
        }

        return token::Token(-1, -1, "", TTYPE_OUTOFRANGE);
    }

    token::Token TokenManager::lookBehind(int spaces)
    {
        if (currentTokenIndex - spaces > 0) {
            return tokens.at(currentTokenIndex - spaces);
        }

        return token::Token(-1, -1, "", TTYPE_OUTOFRANGE);
    }

    token::Token TokenManager::moveToNextToken()
    {
        if (currentTokenIndex + 1 < tokens.size()) {
            if (counting) {
                places++;
            }

            return (currentToken = tokens.at(++currentTokenIndex));
        }

        return token::Token(-1, -1, "", TTYPE_OUTOFRANGE);
    }

    token::Token TokenManager::moveToPreviousToken()
    {
        if (currentTokenIndex - 1 > 0) {
            if (counting) {
                places--;
            }
            return (currentToken = tokens.at(--currentTokenIndex));
        }

        return token::Token(-1, -1, "", TTYPE_OUTOFRANGE);
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

    bool TokenManager::found(TokenType type)
    {
        if (getCurrentToken().getType() == type) {
            return true;
        }
        return false;
    }

    void TokenManager::consume(TokenType type)
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

    bool TokenManager::hasMoreTokens()
    {
        if (currentTokenIndex == tokens.size() - 1) {
            return false;
        }
        return true;
    }

} /* namespace parser */
