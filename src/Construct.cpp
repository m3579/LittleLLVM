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
    Construct::Construct(std::string name, TokenType tokenType, NodeType nodeType, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional) :
        found(found), notFound(notFound), optional(optional), tokenTypes(std::vector<TokenType> { tokenType }), nodeTypes(std::vector<TokenType> { nodeType }), name(name)
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<TokenType> tokenTypes, std::vector<NodeType> nodeTypes, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional) :
        found(found), notFound(notFound), optional(optional), tokenTypes(tokenTypes), nodeTypes(nodeTypes), name(name)
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<SP<Construct>> constructs, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional) :
        found(found), notFound(notFound), optional(optional), constructs(constructs), name(name)
    {
        containsOtherConstructs = true;
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
    std::vector<TokenType> Construct::getTokenTypes()
    {
        return tokenTypes;
    }

    std::vector<NodeType> Construct::getNodeTypes()
    {
        return nodeTypes;
    }

    std::string Construct::getName()
    {
        return name;
    }

    std::vector<SP<Construct>> Construct::getComponents()
    {
        return constructs;
    }

    bool Construct::isOptional()
    {
        return optional;
    }

}
