#ifndef CONSTRUCTTREEFORMNODE_HPP_INCLUDED
#define CONSTRUCTTREEFORMNODE_HPP_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 12, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "SmartPointer.hpp"
#include <vector>

using namespace pointer;

namespace ast
{
    class ConstructTreeFormNode
    {
        public:
            ConstructTreeFormNode(std::string constructName);
            ~ConstructTreeFormNode();

            SP<ConstructTreeFormNode> subnode(std::string node);
            SP<ConstructTreeFormNode> subnode(std::vector<std::string> nodes);

            SP<ConstructTreeFormNode> get(std::string name);
            SP<ConstructTreeFormNode> get(std::vector<std::string> location);

            std::vector<SP<ConstructTreeFormNode>> getSubnodes();

            std::string getConstructName();

            std::string constructName;

        private:
            std::vector<SP<ConstructTreeFormNode>> subnodes;
    };
}


#endif // CONSTRUCTTREEFORMNODE_HPP_INCLUDED
