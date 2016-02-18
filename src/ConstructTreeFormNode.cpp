/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 12, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "utilities.h"
#include "ConstructTreeFormNode.hpp"

namespace ast
{
    ConstructTreeFormNode::ConstructTreeFormNode(std::string name) :
        name(name)
    {

    }

    ConstructTreeFormNode::~ConstructTreeFormNode()
    {

    }

    SP<ConstructTreeFormNode> ConstructTreeFormNode::subnode(std::string node)
    {
        SP<ConstructTreeFormNode> subnode(new ConstructTreeFormNode(node));
        subnodes.push_back(subnode);
        return subnode;
    }

    SP<ConstructTreeFormNode> ConstructTreeFormNode::subnode(std::vector<std::string> nodes)
    {
        std::vector<std::string> original(nodes);
        if (nodes.size() > 0) {
            std::string name = nodes.at(0);
            subnode(name);

            nodes.erase(nodes.begin());
            if (nodes.size() > 0) {
                get(name)->subnode(nodes);
            }
        }

        return get(nodes);
    }

    SP<ConstructTreeFormNode> ConstructTreeFormNode::get(std::string name)
    {
        for (iterate_over(node, subnodes)) {
            if ((*node)->name == name) {
                return *node;
            }
        }

        return SP<ConstructTreeFormNode>();
    }

    SP<ConstructTreeFormNode> ConstructTreeFormNode::get(std::vector<std::string> nodes)
    {
        if (nodes.size() > 1) {
            for (iterate_over(node, subnodes)) {
                if ((*node)->name == nodes.at(0)) {
                    nodes.erase(nodes.begin());
                    return (*node)->get(nodes);
                }
            }
        }
        else if (nodes.size() == 1) {
            for (iterate_over(node, subnodes)) {
                if ((*node)->name == nodes.at(0)) {
                    return *node;
                }
            }
        }

        return SP<ConstructTreeFormNode> (0);
    }
}
