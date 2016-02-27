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
    // TODO: make way for Constructs to be shallow-copied into the parser instead of deep copied so that each construct
    // behaves the same for different occurrences throughout the source code
    // rather than being changed after one occurrence and affecting all of the other occurrences because it is a deep
    // copy
    Construct::Construct(std::string name, TokenType tokenType, NodeType nodeType, ActionAfterParserEvent found, ActionAfterParserEvent notFound) :
        found(found), notFound(notFound), treeForm(0), optional(false), tokenTypes(std::vector<TokenType> { tokenType }), nodeTypes(std::vector<TokenType> { nodeType }),
        name(name)
        // TODO: something like treeForm(new ConstructTreeFormNode(tokenType)) instead of initializing it to 0
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<TokenType> tokenTypes, std::vector<NodeType> nodeTypes, ActionAfterParserEvent found, ActionAfterParserEvent notFound) :
        found(found), notFound(notFound), treeForm(0), optional(false), tokenTypes(tokenTypes), nodeTypes(nodeTypes),
        name(name)
    {
        containsOtherConstructs = false;
    }

    Construct::Construct(std::string name, std::vector<SP<Construct>> constructs, ActionAfterParserEvent found, ActionAfterParserEvent notFound) :
        found(found), notFound(notFound), treeForm(0), optional(false), constructs(constructs),
        name(name)
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

    SP<Construct> Construct::getOptionalForm()
    {
        SP<Construct> copyConstruct(new Construct(*this));
        copyConstruct->setOptional(true);
        return copyConstruct;
    }

    void Construct::setOptional(bool optional)
    {
        this->optional = optional;
    }

    bool Construct::isOptional()
    {
        return optional;
    }
}
