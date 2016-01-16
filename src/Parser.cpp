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

//    SP<ast::SyntaxTree> Parser::createSyntaxTree()
//    {
//        std::vector<token::Token> tokens(lexr.tokenizeSource());
//
//        TokenManager tm(tokens);
//
//        SP<ast::SyntaxTree> tree(new ast::SyntaxTree());
//
//        while (!exit) {
//            bool found = false;
//            for (auto symbol = symbols.begin(); symbol != symbols.end(); ++symbol) {
//                SP<ast::SyntaxTreeComponent> statement(lookFor((*symbol), tm));
//                if (statement) {
//                    tree->add(statement);
//                    found= true;
//                    break;
//                }
//                else {
//                    continue;
//                }
//            }
//
//            if (!found) {
//                if (noFind) {
//                    noFind(tm);
//                }
//            }
//        }
//
//        return tree;
//    }
//
//    SP<ast::SyntaxTreeComponent> Parser::lookFor(SP<ast::Symbol> lookingFor, TokenManager& tm)
//    {
//        if (tm.found(lookingFor->tokenType)) {
//
//            SP<ast::SyntaxTreeComponent> first(new node::Node(tm.getCurrentToken(), lookingFor->nodeType));
//
//            tm.moveToNextToken();
//
//            if (lookingFor->actionAfterFind) {
//                lookingFor->actionAfterFind(tm);
//            }
//
//            std::vector<SP<ast::Symbol>> nextSymbols(lookingFor->possibleNextSymbols);
//
//            for (auto symbol = nextSymbols.begin(); symbol != nextSymbols.end(); ++symbol) {
//                SP<ast::SyntaxTreeComponent> next(lookFor(*symbol, tm));
//
//                if (next) {
//                    SP<ast::Symbol> s(*symbol);
//                    int precedence = lookingFor->precedences[s];
//                    if (precedence > 0) {
//                        next->add(first);
//                        first->root = next;
//                        return next;
//                    }
//                    else {
//                        first->add(next);
//                        next->root = first;
//                        return first;
//                    }
//                }
//            }
//
//            if (lookingFor->noFind) {
//                lookingFor->noFind(tm);
//            }
//
//            return first;
//        }
//
//        return SP<ast::SyntaxTreeComponent>();
//    }

//    SP<ast::SyntaxTree> Parser::createSyntaxTree()
//    {
//        TokenManager tm(lexr.tokenizeSource());
//
//        SP<ast::SyntaxTree> syntaxTree;
//
//        while (!exit) {
//            std::vector<node::Node> nodeList;
//            RecursiveSearchResult result = lookFor(constructs, nodeList);
//
//            if (result == RecursiveSearchResult.NOTFOUND) {
//                this->noFind();
//            }
//            else if (result == RecursiveSearchResult.NOTFOUNDALREADYHANDLED) {
//
//            }
//            else if (result == RecursiveSearchResult.FINISHED) {
//
//            }
//        }
//    }
//
//    RecursiveSearchResult Parser::lookFor(std::vector<ast::Symbols> possibleSymbols, std::vector<node::Node> nodeList, TokenManager& tm)
//    {
//        if (possibleSymbols.size() == 0) {
//            return RecursiveSearchResult.FINISHED;
//        }
//
//        for (iterate_over(symbol, possibleSymbols)) {
//            if (tm.found(symbol.tokenType)) {
//                nodeList.push_back(Node(tm.getCurrentToken(), symbol.nodeType));
//                RecursiveSearchResult result = lookFor(symbol.possibleNextSymbols, nodeList, tm);
//
//                if (result == RecursiveSearchResult.FINISHED) {
//                    return RecursiveSearchResult.FINISHED;
//                }
//                else if (result == RecursiveSearchResult.NOTFOUND) {
//                    symbol.noFind(tm);
//                }
//                else if (result == RecursiveSearchResult.NOTFOUNDALREADYHANDLED) {
//                    return RecursiveSearchResult.NOTFOUNDALREADYHANDLED;
//                }
//                else if (result == RecursiveSearchResult.FINISHED) {
//                    return RecursiveSearchResult.FINISHED;
//                }
//            }
//        }
//
//        return RecursiveSearchResult.NOTFOUND;
//    }

    SP<ast::SyntaxTree> Parser::createSyntaxTree()
    {
        TokenManager tm(lexr.tokenizeSource());

        ast::NodeList nodeList;

        for (iterate_over(construct, constructs)) {
            lookFor(construct);
            // Finish this...
        }
    }

    SP<ast::NodeList> Parser::lookFor(SP<Construct> c, SP<ast::NodeList> nodeList, TokenManager& tm)
    {
        for (iterate_over(consruct, c->symbols)) {
            if (construct->isLeaf()) {
                if (tm.found(construct->getTokenType())) {
                    nodeList->addNode(Node(tm.getCurrentToken(), construct->getDesiredNodeType()));
                    tm.moveToNextToken();
                }
            }
            else {
                nodeList->addNodeList(lookFor(construct, nodeList, tm));
            }
        }

        return nodeList;
    }

    void Parser::addSymbol(SP<ast::Symbol> symbol)
    {
        constructs.push_back(symbol);

        precedences[symbol] = 0;
    }

} /* namespace parser */
