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
                assembleTerminal(Node(Token(), NTYPE_STMT), *terminal, syntaxTree, tm);
            }
        }

        return syntaxTree;
    }

    bool Parser::assembleTerminal(Node supernode, Terminal terminal, SyntaxTree& syntaxTree, TokenManager& tm)
    {
        int type = terminal.getTokenType();

        if (tm.found(type)) {

            terminal.actionAfterFind(tm);

            Node node(tm.getCurrentToken(), terminal.getNodeType());

            supernode.addNode(node);

            std::vector<Terminal> nextTerminals(terminal.getNextTerminals());

            for (auto next = nextTerminals.begin(); next != nextTerminals.end(); ++next) {
                if (assembleTerminal(node, *next, syntaxTree, tm)) {
                    break;
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
