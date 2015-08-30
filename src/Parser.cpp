/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "Parser.h"
#include "Lexer.h"

namespace parser
{
    Parser::Parser(std::string sourceCode, Lexer lexr) :
        sourceCode(sourceCode), lexr(lexr)
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

        for (auto terminal = terminals.begin(); terminal != terminals.end(); ++terminal) {
            assembleTerminal(*terminal, syntaxTree, tm);
        }

        return syntaxTree;
    }

    bool Parser::assembleTerminal(Node supernode, Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm)
    {
        if (tm.found(terminal.getToken().getType())) {

            terminal.actionAfterFind();

            Node node(tm.getCurrentToken(), terminal.getType());

            supernode.add(node);

            std::vector<Terminal> nextTerminals(terminal.getNextTerminals());

            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                if (assembleTerminal(node, next, syntaxTree, tm)) {
                    break;
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
