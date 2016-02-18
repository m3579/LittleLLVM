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
#include "FlatNodeList.hpp"

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

        std::vector<SP<parser::FlatNodeList>> statements;

//        while (!exit) {
            bool found = false;

            for (iterate_over(construct, constructs)) {
                std::cout << "Currently on " << (*construct)->getName() << "\n";

                SP<FlatNodeList> flatNodeList(new FlatNodeList((*construct)->getName()));
                flatNodeList->treeForm = (*construct)->treeForm;

                RecursiveSearchResult result = lookFor(*construct, flatNodeList, tm);

                if (result == RecursiveSearchResult::FINISHED) {
                    std::cout << "Finished\n";
                    statements.push_back(flatNodeList);
                    found = true;
                    break;
                }
            }

            if (!found) {
                noFind(tm);
            }
//        }

        for (iterate_over(statement, statements)) {
            std::cout << "Statement:\n";
            (*statement)->print("");
        }

        SP<ast::SyntaxTree> syntaxTree = assembleSyntaxTree(statements);
        return syntaxTree;
    }

    SP<ast::SyntaxTree> Parser::assembleSyntaxTree(std::vector<SP<parser::FlatNodeList>> statements)
    {
        SP<ast::SyntaxTree> syntaxTree(new ast::SyntaxTree());

        for (iterate_over(it, statements))
        {
            std::cout << "Iterating over statements...\n";
            SP<FlatNodeList> statementFlatNodeList(*it);
            SP<ast::ConstructTreeFormNode> statementTreeForm(statementFlatNodeList->treeForm);

            std::vector<SP<FlatNode>> flatNodePool;
            statementFlatNodeList->populateFlatNodePool(flatNodePool);

            SP<ast::ConstructTreeFormNode> rootConstructTreeFormNode(statementTreeForm);

            std::cout << "Testing with root " << rootConstructTreeFormNode->getConstructName() << "\n";

            SP<FlatNode> matchingFlatNode(findMatchingFlatNode(rootConstructTreeFormNode, flatNodePool));
            if (!matchingFlatNode) {
                // TODO: make better error message for this
                utilities::logError("No matching flat node was found for construct tree form node '" + rootConstructTreeFormNode->getConstructName() + "'");
            }

            SP<node::Node> rootNode(new node::Node(matchingFlatNode->getToken(), matchingFlatNode->getNodeType()));

            assembleSyntaxTreeBranch(rootConstructTreeFormNode, rootNode, flatNodePool);

            syntaxTree->add(rootNode);
        }

        return syntaxTree;
    }

    void Parser::assembleSyntaxTreeBranch(SP<ast::ConstructTreeFormNode> rootTreeFormNode, SP<node::Node> rootNode, std::vector<SP<FlatNode>> flatNodePool)
    {
        std::cout << "Testing with root " << rootTreeFormNode->getConstructName() << "\n";

        std::vector<SP<ast::ConstructTreeFormNode>> treeFormNodeSubnodes(rootTreeFormNode->getSubnodes());

        std::cout << "[";
        for (iterate_over(it, treeFormNodeSubnodes))
        {
            std::cout << (*it)->getConstructName() << ", ";
        }
        std::cout << "]\n";

        for (iterate_over(it, treeFormNodeSubnodes))
        {
            SP<ast::ConstructTreeFormNode> treeFormSubnode(*it);
            std::cout << "Searching for " << treeFormSubnode->getConstructName() << "\n";
            SP<FlatNode> matchingFlatNode(findMatchingFlatNode(treeFormSubnode, flatNodePool));
            if (!matchingFlatNode) {
                // TODO: error message should be a constant string defined somewhere
                utilities::logError("No matching flat node was found for construct tree form node '" + rootTreeFormNode->getConstructName() + "'");
            }

            SP<node::Node> subnode(new node::Node(matchingFlatNode->getToken(), matchingFlatNode->getNodeType()));
            rootNode->add(subnode);

            assembleSyntaxTreeBranch(treeFormSubnode, subnode, flatNodePool);
        }
    }

    SP<FlatNode> Parser::findMatchingFlatNode(SP<ast::ConstructTreeFormNode> constructTreeFormNode, std::vector<SP<FlatNode>> flatNodePool)
    {
        for (iterate_over(it, flatNodePool))
        {
            SP<FlatNode> flatNode(*it);
            std::cout << "Testing flat node: " << flatNode->getName() << "\n";

            if (flatNode->getName() == constructTreeFormNode->getConstructName()) {
                std::cout << "Found match with " << flatNode->getName() << "\n";
                return flatNode;
            }
        }

        return SP<FlatNode>();
    }

    RecursiveSearchResult Parser::lookFor(SP<ast::Construct> c, SP<parser::FlatNodeList> nodeList, TokenManager& tm)
    {
        std::cout << "Looking for " << c->getName() << "\n";
        std::cout << c->getComponents().size() << "\n";

        std::vector<SP<ast::Construct>> components(c->getComponents());

        int i = 0;
        for (iterate_over(construct, components)) {
            std::cout << "Iteration " << ++i << "\n";
            if ((*construct)->isLeaf()) {
                if (tm.found((*construct)->getTokenType())) {
                    std::cout << "Found " << tm.getCurrentToken().getText() << " of type " << tm.getCurrentToken().getType() << "\n";
                    nodeList->addFlatNodeListItem(SP<FlatNode> (new FlatNode((*construct)->getName(), tm.getCurrentToken(), (*construct)->getNodeType())));
                    tm.moveToNextToken();
                }
                else {
                    std::cout << "Not found " << (*construct)->getTokenType() << "\n";
                    return RecursiveSearchResult::NOTFOUND;
                }
            }
            else {
                SP<FlatNodeList> constructNodeList(new FlatNodeList((*construct)->getName()));
                constructNodeList->treeForm = (*construct)->treeForm;
                RecursiveSearchResult result = lookFor(*construct, constructNodeList, tm);
                if (result == RecursiveSearchResult::NOTFOUND) {
                    (*construct)->noFind(tm);
                    return RecursiveSearchResult::NOTFOUNDALREADYHANDLED;
                }
                else if (result == RecursiveSearchResult::NOTFOUNDALREADYHANDLED) {
                    return RecursiveSearchResult::NOTFOUNDALREADYHANDLED;
                }
                else {
                    nodeList->addFlatNodeListItem(constructNodeList);
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
