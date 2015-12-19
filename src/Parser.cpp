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
#include "../utilities.h"

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

    std::shared_ptr<ast::SyntaxTree> Parser::createSyntaxTree()
    {
        std::vector<token::Token> tokens(lexr.tokenizeSource());

        TokenManager tm(tokens);

        std::shared_ptr<ast::SyntaxTree> tree(new ast::SyntaxTree());

        while (!exit) {
            bool found = false;
            for (auto symbol = symbols.begin(); symbol != symbols.end(); ++symbol) {
                std::shared_ptr<node::Node> statement(lookFor((*symbol), tm));
                if (statement) {
                    tree->add(statement);
                    found = true;
                    break;
                }
                else {
                    continue;
                }
            }

            if (!found) {
                if (noFind) {
                    noFind(tm);
                }
            }
        }

        return tree;
    }

    std::shared_ptr<node::Node> Parser::lookFor(std::shared_ptr<ast::Symbol> lookingFor, TokenManager& tm)
    {
        if (tm.found(lookingFor->tokenType)) {

            std::shared_ptr<node::Node> first(new node::Node(tm.getCurrentToken(), lookingFor->nodeType));

            tm.moveToNextToken();

            if (lookingFor->actionAfterFind) {
                lookingFor->actionAfterFind(tm);
            }

            std::vector<std::shared_ptr<ast::Symbol>> nextSymbols(lookingFor->possibleNextSymbols);

            for (auto symbol = nextSymbols.begin(); symbol != nextSymbols.end(); ++symbol) {
                std::shared_ptr<node::Node> next = lookFor(*symbol, tm);

                if (next) {
                    if (lookingFor->precedences[*symbol] > 0) {
                        next->add(first);
                        return next;
                    }
                    else {
                        first->add(next);
                        return first;
                    }
                }
            }

            if (lookingFor->noFind) {
                lookingFor->noFind(tm);
            }

            return first;
        }

        return std::shared_ptr<node::Node> { };
    }

    void Parser::addSymbol(std::shared_ptr<ast::Symbol> symbol)
    {
        symbols.push_back(symbol);

        precedences[symbol] = 0;
    }

    bool Parser::tryToFindSymbol(std::shared_ptr<ast::Symbol> symbol, std::shared_ptr<ast::Branchable> root, parser::TokenManager& tm, std::map<std::shared_ptr<ast::Symbol>, int> precedences)
    {
        TokenType type = symbol->tokenType;

        if (tm.found(type)) {
            std::shared_ptr<node::Node> newNode(new node::Node(tm.getCurrentToken(), symbol->nodeType));

            if (symbol->actionAfterFind != nullptr) {
                symbol->actionAfterFind(tm);
            }

            int precedence = precedences[symbol];
            if (precedence > 0) {
                std::shared_ptr<ast::Branchable> nodeToAddTo(root);

                // Move up the hierarchy
                // (start at 1 because I already moved up one when I initialized nodeToAddTo to root)
                for (int i = 1; i < precedence; i++) {
                    nodeToAddTo = root->root;

                    if (nodeToAddTo == nullptr) {
                        utilities::logError("The precedence level is too high for symbol " + symbol->name);
                    }
                }

                nodeToAddTo->add(newNode);
            }
            else {
                root->add(newNode);
            }

            std::vector<std::shared_ptr<ast::Symbol>> nextSymbols;

            std::map<std::shared_ptr<ast::Symbol>, int> nextSymbolMap(symbol->getNextSymbols());

            for (auto it = nextSymbolMap.begin(); it != nextSymbolMap.end(); ++it) {
                nextSymbols.push_back(it->first);
            }

            if (nextSymbols.size() == 0) {
                return true;
            }

            tm.moveToNextToken();
            bool found = false;
            for (auto next = nextSymbols.begin(); next != nextSymbols.end(); ++next) {
                found = tryToFindSymbol(*next, newNode, tm, symbol->precedences);
                if (found) {
                    break;
                }
            }

            if (!found) {
                // If there was SUPPOSED to be a next token
                if (symbol->noFind) {
                    symbol->noFind(tm);
                }
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
