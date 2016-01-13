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

using smartPointer;

namespace ast
{
    class ConstructTreeFormNode
    {
        public:
            ConstructTreeFormNode(std::string name);
            ~ConstructTreeFormNode();

            SP<ConstructTreeFormNode> subnode(std::string node);
            SP<ConstructTreeFormNode> subnode(std::vector<std::string> nodes);

            SP<ConstructTreeFormNode> get(std::string name);
            SP<ConstructTreeFormNode> get(std::vector<std::string> location);

        private:
            std::string name;

            std::vector<SP<ConstructTreeFormNode>> subnodes;
    };
}


#endif // CONSTRUCTTREEFORMNODE_HPP_INCLUDED
