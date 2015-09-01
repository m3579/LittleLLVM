/*
 * Parser.cpp
 *
 * /TheCompilerFramework/Sources/src/Parser.cpp
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

#include "Parser.h"
#include "Lexer.h"
#include "TokenManager.h"
#include "../TokenType.h"
#include "../NodeType.h"

namespace parser
{
    bool exit = false;

    Parser::Parser(Lexer lexr) :
        lexr(lexr)
    {

    }

    Parser::~Parser()
    {

    }

    SyntaxTree Parser::createSyntaxTree()
    {
        SyntaxTree syntaxTree;

        std::vector<Token> tokens(lexr.tokenizeSource());

        TokenManager tm(tokens);

        while (tm.hasMoreTokens()) {
            bool found;
            for (auto terminal = terminals.begin(); terminal != terminals.end(); ++terminal) {
                found = assembleTerminal(**terminal, syntaxTree, tm);
                if (found) {
                    break;
                }
            }

            if (found) {
                continue;
            }
            else {
                noFind(tm);
            }

            if (exit) {
                break;
            }
        }

        return syntaxTree;
    }

    void Parser::addTerminal(Terminal& terminal)
    {
        terminals.push_back(&terminal);
    }

    bool Parser::assembleTerminal(Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm)
    {
        int type = terminal.getTokenType();

        if (tm.found(type)) {

            syntaxTree.addStatement(terminal.actionAfterFind(tm));

            std::vector<Terminal*> nextTerminals(terminal.getNextTerminals());

            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                bool found = assembleTerminal(**next, syntaxTree, tm);
                if (found) {
                    break;
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
