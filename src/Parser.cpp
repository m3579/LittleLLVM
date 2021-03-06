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
        notFound(0), lexr(lexr)
    {

    }

    Parser::~Parser()
    {

    }

    SP<ast::SyntaxTree> Parser::createSyntaxTree()
    {
        TokenManager tm(lexr.tokenizeSource());

        std::vector<SP<parser::FlatNodeList>> statements;

        int statementCounter = 0;
        while (!tm.exit) {
            statementCounter++;

            bool found = false;
            for (iterate_over(construct, constructs)) {
                std::cout << "\nCurrently on top level construct " << (*construct)->name << "\n";

                SP<FlatNodeList> flatNodeList(new FlatNodeList((*construct)->name));
                flatNodeList->treeForm = (*construct)->treeForm;

                RecursiveSearchResult result = lookFor(*construct, flatNodeList, tm);

                if (tm.exit) {
                    break;
                }

                if (result == RecursiveSearchResult::FINISHED) {
                    std::cout << "Finished\n";
                    statements.push_back(flatNodeList);
                    if ((*construct)->found != 0) {
                        (*construct)->found(tm);
                    }
                    found = true;
                    break;
                }
                else if (result == RecursiveSearchResult::NOTFOUNDERRORHANDLED) {
                    continue;
                }
            }

            if (!found) {
                if (notFound != 0) {
                    notFound(tm);
                }
            }
        }

        for (iterate_over(statement, statements)) {
            std::cout << "Statement:\n";
            (*statement)->print("");
        }

        SP<ast::SyntaxTree> syntaxTree = assembleSyntaxTree(statements);
        return syntaxTree;
    }

    RecursiveSearchResult Parser::lookFor(SP<ast::Construct> c, SP<parser::FlatNodeList> nodeList, TokenManager& tm)
    {
        std::cout << "\nLooking for " << c->name << "\n";
        std::cout << "Construct's component list size: " << c->components.size() << "\n";

        if (c->instantiator != 0) {
            std::cout << "Used instantiator\n";
            c = c->instantiator();
        }

        if (c->constructs.size() > 0) {
            std::cout << "Alternate constructs' size is greater than 0\n";
            std::vector<SP<ast::Construct>> constructs(c->constructs);

            bool found = false;

            for (iterate_over(construct, constructs)) {
                // I make this new construct because otherwise,
                // the construct will go by its name (i.e. "Number")
                // instead of the generic name the alternating construct
                // was given (i.e. "Value") and the treeForm (which uses the alternating
                // construct's name) will be confused
                SP<ast::Construct> properlyNamedConstruct(*construct);
                properlyNamedConstruct->name = c->name;

                RecursiveSearchResult result = lookFor(properlyNamedConstruct, nodeList, tm);
                if (result == RecursiveSearchResult::FINISHED) {
                    found = true;
                    break;
                }
                else {
                    continue;
                }
            }

            if (!found) {
                if (c->notFound != 0) {
                    c->notFound(tm);
                }
            }
        }
        else {
            std::cout << "Alternate constructs' size is not greater than 0\n";

            if (c->isLeaf()) {
                std::cout << "Construct is leaf\n";
                bool foundConstruct = false;
                std::vector<TokenType> tokenTypes(c->tokenTypes);

                std::cout << "Currently on |" << tm.getCurrentToken().getText() << "|\n";

                int i = -1;
                for (iterate_over(tokenType, tokenTypes)) {
                    i++;
                    if (tm.found(*tokenType)) {
                        // TODO: decide whether optional nodes should be added to the flat node list
                        if (!(c->optional)) {
                            std::cout << "Found leaf construct |" << c->name << "|\n";
                            nodeList->addFlatNodeListItem(SP<FlatNode> (new FlatNode(c->name, tm.getCurrentToken(), c->nodeTypes.at(i))));
                        }
                        tm.moveToNextToken();

                        std::cout << "Found\n";

                        if (c->found != 0) {
                            c->found(tm);
                        }

                        foundConstruct = true;
                    }
                }

                if (!foundConstruct) {
                    std::cout << "Not found " << c->name << " with token type " << c->tokenTypes.at(0) << "\n";

                    if (!(c->optional)) {
                        std::cout << "Construct is not optional\n";
                        if (c->notFound != 0) {
                            c->notFound(tm);
                        }

                        return RecursiveSearchResult::NOTFOUNDERRORHANDLED;
                    }
                    else {
                        std::cout << "Construct is optional\n";
                    }
                }
            }
            else {
                std::cout << "Construct is not leaf\n";

                std::vector<SP<ast::Construct>> components(c->components);

                int i = 0;
                for (iterate_over(component, components)) {
                    std::cout << "Iteration " << ++i << "\n";

                    SP<FlatNodeList> componentNodeList(new FlatNodeList((*component)->name));
                    componentNodeList->treeForm = (*component)->treeForm;
                    RecursiveSearchResult result = lookFor(*component, componentNodeList, tm);

                    if (result == RecursiveSearchResult::NOTFOUNDERRORHANDLED) {
                        if (!((*component)->optional)) {
                            std::cout << "Not found, and construct '" << c->name << "' is not optional\n";
                            return RecursiveSearchResult::NOTFOUNDERRORHANDLED;
                        }
                        else {
                            std::cout << "Not found, but construct '" << c->name << "' is optional\n";
                        }
                    }
                    else {
                        // We found a node belonging to this construct, we have
                        // to find the rest of it (or at least the non-optional parts)
                        // If we leave it as optional, then the compiler will continue if we don't find
                        // the rest of it
                        // So we make it non-optional
                        if (c->optional) {
                            c->optional = false;
                            std::cout << "Set optional construct to not optional\n";
                        }

                        nodeList->addFlatNodeListItem(componentNodeList);
                        if ((*component)->found != 0) {
                            (*component)->found(tm);
                        }
                    }
                }
            }
        }


        return RecursiveSearchResult::FINISHED;
    }

    // TODO: make way to ensure that user sets the Construct::treeForm member by the time they add
    // the construct to the parser
    SP<ast::SyntaxTree> Parser::assembleSyntaxTree(std::vector<SP<parser::FlatNodeList>> statements)
    {
        SP<ast::SyntaxTree> syntaxTree(new ast::SyntaxTree());

        for (iterate_over(it, statements))
        {
            std::cout << "Iterating over statements...\n";
            SP<FlatNodeList> statementFlatNodeList(*it);
            SP<ast::ConstructTreeFormNode> statementTreeForm(statementFlatNodeList->treeForm);

            std::cout << "Statement flat node list:\n";
            statementFlatNodeList->print("");

            std::vector<SP<FlatNode>> flatNodePool;
            statementFlatNodeList->populateFlatNodePool(flatNodePool);

            SP<ast::ConstructTreeFormNode> rootConstructTreeFormNode(statementTreeForm);

            std::cout << "Testing root construct tree form node |" << rootConstructTreeFormNode->constructName << "|\n";

            SP<FlatNode> matchingFlatNode(findMatchingFlatNode(rootConstructTreeFormNode, flatNodePool));
            if (!matchingFlatNode) {
                // TODO: make flag so that if none of the roots are found, then an error occurs
                utilities::logError("Could not find matching flat node for construct " + rootConstructTreeFormNode->constructName);
                break;
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
                // TODO: make flag so that if none of the roots are found, then an error occurs
                continue;
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

    void Parser::addConstruct(SP<ast::Construct> construct)
    {
        constructs.push_back(construct);
    }

} /* namespace parser */
