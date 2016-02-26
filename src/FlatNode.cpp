/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 17, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <iostream>

#include "FlatNode.hpp"

namespace parser
{
    FlatNode::FlatNode(std::string name, token::Token token, NodeType nodeType) :
        FlatNodeListItem(), token(token), nodeType(nodeType), name(name)
    {

    }

    FlatNode::~FlatNode()
    {

    }

    void FlatNode::print(std::string tabs)
    {
        std::cout << tabs << "Flat Node |" << name << "|:\n"
                  << tabs << "\t|" << token.getText() << "|\n"
                  << tabs << "\t" << token.getType() << "\n"
                  << tabs << "\tAt line " << token.getLineNumber() << " column " << token.getColumnNumber()
                  << "\n";
    }

    bool FlatNode::isLeaf()
    {
        return true;
    }

    std::string FlatNode::getName()
    {
        return name;
    }

    token::Token FlatNode::getToken()
    {
        return token;
    }

    NodeType FlatNode::getNodeType()
    {
        return nodeType;
    }
}
