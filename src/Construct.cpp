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

#include "Construct.h"

namespace ast
{
    Construct::Construct(std::string name, TokenType tokenType, NodeType nodeType) :
        tokenType(tokenType), nodeType(nodeType), name(name)
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<SP<Construct>> constructs) :
        constructs(constructs)
    {

    }

    Construct::~Construct()
    {

    }

    Construct Construct::setTreeForm(SP<TreeForm> treeForm)
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

    std::string Construct::getName()
    {
        return name;
    }
}
