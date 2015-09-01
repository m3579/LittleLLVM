/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <iostream>

#include "Node.h"

namespace node
{
    Node::Node(Token token, int type) :
        token(token), type(type)
    {

    }

    Node::~Node()
    {

    }

    void Node::addNode(Node node)
    {
        nodes.push_back(node);
    }

    Node Node::getNode(unsigned int index)
    {
        if (index >= 0 && index < nodes.size()) {
            return nodes.at(index);
        }

        return Node();
    }

    void Node::print(std::string tabs)
    {
        std::cout << tabs << "Node: " << token.getText() << "\n"
                  << tabs << "\tType: " << type
                  << "\n";
    }

} /* namespace node */
