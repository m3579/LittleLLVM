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

#include <iostream>

#include "NodeList.hpp"
#include "SingleNodeListItem.hpp"
#include "utilities.h"

namespace parser
{
    NodeList::NodeList() :
        NodeListItem()
    {

    }

    NodeList::~NodeList()
    {

    }

    void NodeList::addNode(SP<SingleNodeListItem> node)
    {
        nodes.push_back(node);
    }

    void NodeList::addNodeList(SP<NodeList> nodeList)
    {
        nodes.push_back(nodeList);
    }

    void NodeList::print(std::string tabs)
    {
        std::cout << tabs << "NodeList:\n";
        for (iterate_over(node, nodes))
        {
            (*node)->print(tabs + "\t");
        }
    }

}
