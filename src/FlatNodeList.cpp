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

#include "FlatNodeList.hpp"
#include "SingleNodeListItem.hpp"
#include "utilities.h"

namespace parser
{
    FlatNodeList::FlatNodeList(std::string name) :
        FlatNodeListItem(), name(name)
    {

    }

    FlatNodeList::~FlatNodeList()
    {

    }

    void FlatNodeList::addFlatNodeListItem(SP<FlatNodeListItem> flatNodeListItem)
    {
        nodes.push_back(flatNodeListItem);
    }

    void FlatNodeList::print(std::string tabs)
    {
        std::cout << tabs << "NodeList:\n";
        for (iterate_over(node, nodes))
        {
            (*node)->print(tabs + "\t");
        }
    }

    std::vector<SP<FlatNodeListItem>> FlatNodeList::getNodes()
    {
        return nodes;
    }

    bool FlatNodeList::isLeaf()
    {
        return false;
    }

    std::string FlatNodeList::getName()
    {
        return name;
    }

    void FlatNodeList::populateFlatNodePool(std::vector<SP<FlatNode>>& flatNodePool)
    {
        for (iterate_over(it, nodes))
        {
            SP<FlatNodeListItem> flatNodeListItem(*it);

            if (flatNodeListItem->isLeaf()) {
                flatNodePool.push_back(std::dynamic_pointer_cast<FlatNode>(flatNodeListItem));
            }
            else {
                (std::dynamic_pointer_cast<FlatNodeList>(flatNodeListItem))->populateFlatNodePool(flatNodePool);
            }
        }
    }
}
