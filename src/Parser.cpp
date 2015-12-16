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
 *        Usage: The parser contains a list of Symbols. The parser will look for a match with the current Token it is parsing;
 *               if it finds one, then it
 *               will invoke the Symbol's actionAfterFind method. The user is responsible for returning a Node from the
 *               actionAfterFind. That node will be added to the AST to represent any nonsymbols that follow the symbol
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

        if (tokens.size() == 0) {
            return ast::SyntaxTree { };
        }

        if (symbols.size() == 0) {
            return ast::SyntaxTree { };
        }

        parser::TokenManager tm(tokens);

        while (true) {
            bool found = false;
            for (auto symbol = symbols.begin(); symbol != symbols.end(); ++symbol) {
                found = tryToFindSymbol(**symbol, &syntaxTree, tm);
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

    void Parser::addSymbol(ast::Symbol& symbol)
    {
        symbols.push_back(&symbol);
    }

    bool Parser::tryToFindSymbol(ast::Symbol symbol, Branchable* root, parser::TokenManager& tm)
    {
        TokenType type = symbol.getTokenType();

        if (tm.found(type)) {

            Node newRoot(tm.getCurrentToken(), symbol.nodeType);

            if (symbol.actionAfterFind != nullptr) {
                symbol.actionAfterFind(tm);
            }

            if (symbol.precedence > 0) {
                Branchable* nodeToAddTo = root;

                // Move up the hierarchy
                for (int i = 0; i < symbol.precedence; i++) {
                    nodeToAddTo = root.rootNode;

                    if (nodeToAddTo == nullptr) {
                        utilities::logError("The precedence level is too high for symbol " + symbol.name);
                    }
                }

                nodeToAddTo.add(newRoot));
            }
            else {
                root.add(newRoot);
            }

            std::vector<ast::Symbol*> nextSymbols(symbol.getNextSymbols());

            tm.moveToNextToken();
            bool found = false;
            for (auto next = nextSymbols.begin(); next != nextSymbols.end(); ++next) {
                found = tryToFindSymbol(**next, &newRoot, tm);
                if (found) {
                    break;
                }
            }

            if (!found) {
                // If there was SUPPOSED to be a next token
                if (symbol.noFind != nullptr) {
                    symbol.noFind(tm);
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
