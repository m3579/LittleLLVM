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

#include "ConstructTreeFormNode.hpp"

namespace ast
{
    ConstructTreeFormNode::ConstructTreeFormNode(std::string name) :
        name(name)
    {

    }

    SP<ConstructTreeFormNode> subnode(std::string node)
    {
        subnodes.push_back(node);
    }

    SP<ConstructTreeForm> subnode(std::vector<std::string> nodes)
    {
        subnodes.insert(subnodes.end(), nodes.begin(), nodes.end());
    }

    SP<ConstructTreeFormNode> get(std::string name)
    {
        for (auto node = subnodes.begin(); node != subnodes.end(); ++node) {
            if (node.name == name) {
                return node;
            }
        }

        return SP<ConstructTreeFormNode>();
    }

    SP<ConstructTreeFormNode> get(std::vector<std::string> nodes)
    {
        if (nodes.size() > 1) {
            for (auto node = subnodes.begin(); node != subnodes.end(); ++node) {
                if (node.name == nodes.at(0)) {
                    nodes.erase(nodes.begin());
                    return node.get(nodes);
                }
            }
        }
        else if (nodes.size == 1) {
            for (auto node = subnodes.begin(); node != subnodes.end(); ++node) {
                if (node.name == nodes.at(0)) {
                    return node;
                }
            }
        }
    }
}
