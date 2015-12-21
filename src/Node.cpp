/*
 * Node.cpp
 *
 * /TheCompilerFramework/Sources/src/Node.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose: Represents a branch or leaf on the AST. A node wraps a token, and can contain other tokens.
 *
 *        Usage: Will be generated by the Parser's astAction methods. The Parser will then add the Nodes
 *               to the AST.
 *
 *        Notes:
 *
 */

#include <iostream>

#include "Node.hpp"

namespace node
{
    Node::Node(token::Token token, NodeType type, WP<ast::Branchable> root) :
        Branchable(root), token(token), type(type)
    {

    }

    Node::~Node()
    {

    }

    void Node::add(SP<ast::Branchable> n)
    {
        nodes.insert(nodes.begin(), n);
    }

    SP<ast::Branchable> Node::getNode(unsigned int index)
    {
        if (index >= 0 && index < nodes.size()) {
            return nodes.at(index);
        }

        return SP<ast::Branchable>();
    }

    void Node::print(std::string tabs)
    {
        std::cout << tabs << "Node: |" << token.getText() << "|\n"
                  << tabs << "\tType: " << type << "\n"
                  << tabs << "\tSubnodes:\n\n";

        for (auto node = nodes.begin(); node != nodes.end(); ++node) {
            (*node)->print(tabs + "\t\t");
        }
    }

} /* namespace node */
