/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 21, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <cstdarg>
#include <iostream>

#include "Construct.hpp"

namespace ast
{
    Construct::Construct(std::string name, TokenType tokenType, NodeType nodeType) :
        tokenType(tokenType), nodeType(nodeType), name(name)
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<SP<Construct>> constructs) :
        constructs(constructs), name(name)
    {

    }

    Construct::~Construct()
    {

    }

    Construct Construct::setTreeForm(SP<ConstructTreeFormNode> treeForm)
    {
        this->treeForm = treeForm;
        return *this;
    }

    bool Construct::isLeaf()
    {
        return !containsOtherConstructs;
    }

    bool Construct::isBranch()
    {
        return containsOtherConstructs;
    }

    // TODO rename these to something better
    TokenType Construct::getTokenType()
    {
        return tokenType;
    }

    NodeType Construct::getNodeType()
    {
        return nodeType;
    }

    std::string Construct::getName()
    {
        return name;
    }

    std::vector<SP<Construct>> Construct::getComponents()
    {
        return constructs;
    }

    void Construct::setActionAfterConstructNotFound(AstManipulationAction action)
    {
        noFindAction = action;
    }

    void Construct::noFind(parser::TokenManager& tm)
    {
        noFindAction(tm);
    }
}
