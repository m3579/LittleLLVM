/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 16, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "NodeList.hpp"

namespace ast
{

    NodeList::NodeList()
    {

    }

    NodeList::~NodeList()
    {

    }

    void NodeList::addNode(SP<Node> node)
    {
        nodes.push_back(node);
    }

    void NodeList::addNodeList(SP<NodeList> nodeList)
    {
        nodes.push_back(nodeList);
    }

}
