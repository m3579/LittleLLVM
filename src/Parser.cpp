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

#include <iostream>

#include "Parser.h"
#include "Lexer.h"
#include "TokenManager.h"
#include "../TokenType.h"
#include "../NodeType.h"

namespace parser
{

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
            for (auto terminal = terminals.begin(); terminal != terminals.end(); ++terminal) {
                assembleTerminal(*terminal, syntaxTree, tm);
            }
        }

        return syntaxTree;
    }

    void Parser::addTerminal(Terminal& terminal)
    {
        terminals.push_back(terminal);
    }

    bool Parser::assembleTerminal(Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm)
    {
        int type = terminal.getTokenType();

        if (tm.found(type)) {

            Node node(terminal.actionAfterFind(tm));

            syntaxTree.addStatement(node);

            std::vector<Terminal> nextTerminals(terminal.getNextTerminals());

            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                if (assembleTerminal(*next, syntaxTree, tm)) {
                    break;
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
