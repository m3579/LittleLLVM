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
#include "TokenType.h"
#include "NodeType.h"
#include "utilities.h"
#include "NodeList.hpp"

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

        std::vector<SP<parser::NodeList>> statements;

        while (!exit) {
            bool found = false;

            for (iterate_over(construct, constructs)) {
                SP<parser::NodeList> nodeList(new parser::NodeList());
                RecursiveSearchResult result = lookFor(*construct, nodeList, tm);
                if (result == RecursiveSearchResult::FINISHED) {
                    statements.push_back(nodeList);
                    found = true;
                    break;
                }
            }

            if (!found) {
                noFind(tm);
            }
        }

        SP<ast::SyntaxTree> syntaxTree = assembleSyntaxTree(statements);
        return syntaxTree;
    }

    RecursiveSearchResult Parser::lookFor(SP<ast::Construct> c, SP<parser::NodeList> nodeList, TokenManager& tm)
    {
        for (iterate_over(construct, c->getComponents())) {
            if ((*construct)->isLeaf()) {
                if (tm.found((*construct)->getTokenType())) {
                    nodeList->addNode(SP<SingleNodeListItem> (new SingleNodeListItem(tm.getCurrentToken(), (*construct)->getNodeType())));
                    tm.moveToNextToken();
                }
                else {
                    return RecursiveSearchResult::NOTFOUND;
                }
            }
            else {
                SP<parser::NodeList> constructNodeList(new parser::NodeList());
                RecursiveSearchResult result = lookFor(*construct, constructNodeList, tm);
                if (result == RecursiveSearchResult::NOTFOUND) {
                    (*construct)->noFind(tm);
                    return RecursiveSearchResult::NOTFOUNDALREADYHANDLED;
                }
                else if (result == RecursiveSearchResult::NOTFOUNDALREADYHANDLED) {
                    return RecursiveSearchResult::NOTFOUNDALREADYHANDLED;
                }
                else {
                    nodeList->addNodeList(constructNodeList);
                }
            }
        }

        return RecursiveSearchResult::FINISHED;
    }

    void Parser::addConstruct(SP<ast::Construct> construct)
    {
        constructs.push_back(construct);
    }

} /* namespace parser */
