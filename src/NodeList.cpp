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
#include "SingleNodeListItem.hpp"

namespace parser
{

    NodeList::NodeList()
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

}
