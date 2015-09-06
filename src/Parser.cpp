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

#include "Parser.hpp"
#include "Lexer.hpp"
#include "TokenManager.hpp"
#include "../TokenType.h"
#include "../NodeType.h"

namespace parser
{
    bool exit = false;

    Parser::Parser(lexer::Lexer lexr) :
        lexr(lexr)
    {

    }

    Parser::~Parser()
    {

    }

    ast::SyntaxTree Parser::createSyntaxTree()
    {
        ast::SyntaxTree syntaxTree;

        std::vector<token::Token> tokens(lexr.tokenizeSource());

        parser::TokenManager tm(tokens);

        while (true) {
            bool found;
            for (auto terminal = terminals.begin(); terminal != terminals.end(); ++terminal) {
                found = assembleTerminal(**terminal, syntaxTree, tm);
                if (found) {
                    break;
                }
            }

            if (exit) {
                break;
            }

            if (found) {
                continue;
            }
            else {
                if (noFind != nullptr) {
                    noFind(tm);
                }
            }

        }

        return syntaxTree;
    }

    void Parser::addTerminal(ast::Terminal& terminal)
    {
        terminals.push_back(&terminal);
    }

    bool Parser::assembleTerminal(ast::Terminal terminal, ast::SyntaxTree& syntaxTree, parser::TokenManager& tm)
    {
        int type = terminal.getTokenType();

        if (tm.found(type)) {

            syntaxTree.addStatement(terminal.actionAfterFind(tm));

            std::vector<ast::Terminal*> nextTerminals(terminal.getNextTerminals());

            bool found;
            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                found = assembleTerminal(**next, syntaxTree, tm);
                if (found) {
                    break;
                }
            }

            if (!found) {
                if (terminal.noFind != nullptr) {
                    terminal.noFind(tm);
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
