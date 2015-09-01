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
                assembleTerminal(**terminal, syntaxTree, tm);
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

        std::cout << "\n\n------" << terminal.id << "------\n";

        std::cout << "Actual: " << tm.getCurrentToken().getType() << "\n";
        std::cout << "Desired: " << type << "\n";

        if (tm.found(type)) {

            std::cout << "\nFound!\n\n";

            syntaxTree.addStatement(terminal.actionAfterFind(tm));

            std::vector<Terminal*> nextTerminals(terminal.getNextTerminals());

            syntaxTree.print("");

            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                bool found = assembleTerminal(**next, syntaxTree, tm);
                if (found) {
                    break;
                }
            }

            std::cout << "\n\n";

            return true;
        }

        std::cout << "\n\n";

        return false;
    }

} /* namespace parser */
