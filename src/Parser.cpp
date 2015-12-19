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
        std::shared_ptr<ast::SyntaxTree> syntaxTree(new ast::SyntaxTree());

        std::vector<token::Token> tokens(lexr.tokenizeSource());

        if (tokens.size() == 0) {
            std::shared_ptr<ast::SyntaxTree> emptyTree(new ast::SyntaxTree());
            return emptyTree;
        }

        if (symbols.size() == 0) {
            std::shared_ptr<ast::SyntaxTree> emptyTree(new ast::SyntaxTree());
            return emptyTree;
        }

        parser::TokenManager tm(tokens);

        while (true) {
            bool found = false;
            for (auto symbol = symbols.begin(); symbol != symbols.end(); ++symbol) {
                found = tryToFindSymbol(syntaxTree, *symbol, syntaxTree, tm, precedences);
                if (found) {
                    syntaxTree->print("\t");
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

    void Parser::addSymbol(std::shared_ptr<ast::Symbol> symbol)
    {
        symbols.push_back(symbol);

        precedences[symbol] = 0;
    }

    bool Parser::tryToFindSymbol(std::shared_ptr<ast::SyntaxTree> tree, std::shared_ptr<ast::Symbol> symbol, std::shared_ptr<ast::Branchable> root, parser::TokenManager& tm, std::map<std::shared_ptr<ast::Symbol>, int> precedences)
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
                for (int i = 0; i < precedence; i++) {
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

            tree->print("");

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
                found = tryToFindSymbol(tree, *next, newNode, tm, symbol->precedences);
                if (found) {
                    break;
                }
            }

            if (!found) {
                std::cout << "Did not find\n";
                // If there was SUPPOSED to be a next token
                if (symbol->noFind != nullptr) {
                    std::cout << "About to run noFind\n";
                    //symbol->noFind(tm);
                    std::cout << "Ran noFind\n";
                }

                std::cout << "Reached here\n";
            }

            return true;
        }

        return false;
    }

} /* namespace parser */
