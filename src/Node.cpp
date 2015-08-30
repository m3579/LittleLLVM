/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

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

} /* namespace node */
