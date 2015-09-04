/*
 * Parser.cpp
 *
 * /TheCompilerFramework/Sources/src/Parser.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose: Takes tokens from the lexer and assembles them into an Abstract Syntax Tree. In this case, the parser
 *               creates and returns a SyntaxTree object.
 *
 *        Usage: The parser contains a list of Terminals. (By the way, I do not use the strict definitions of "terminal" and
 *               "nonterminal". The parser will look for a match with the current Token it is parsing; if it finds one, then it
 *               will invoke the Terminal's actionAfterFind method. The user is responsible for returning a Node from the
 *               actionAfterFind. That node will be added to the AST to represent any nonterminals that follow the terminal.
 *               Each of these nodes will be added directly to the SyntaxTree object; to add Nodes to other Nodes, you will
 *               have to do that in the actionAfterFind method.
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
