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

    Construct::Construct(std::string name, std::vector<SP<Construct>> components, ActionAfterParserEvent found, ActionAfterParserEvent notFound) :
        found(found), notFound(notFound), components(components), name(name)
    {
        containsOtherConstructs = true;
    }

    // TODO: automatically create construct tree form for this case, where the tree form should always just be
    // the construct itself
    Construct::Construct(std::vector<SP<Construct>> constructs, std::string name, ActionAfterParserEvent found, ActionAfterParserEvent notFound) :
        found(found), notFound(notFound), treeForm(0), optional(false), constructs(constructs),
        name(name)
    {
        containsOtherConstructs = false;
    }

    // TODO: initialize all of the other members (do this in the other constructors as well)
    Construct::Construct(LinkConstructReferenceInstantiator instantiator) :
        instantiator(instantiator)
    {

    }

    Construct::~Construct()
    {

    }

    bool Construct::isLeaf()
    {
        return !containsOtherConstructs;
    }

    bool Construct::isBranch()
    {
        return containsOtherConstructs;
    }
}
