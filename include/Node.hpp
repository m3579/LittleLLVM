/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#ifndef NODE_H
#define NODE_H

#include <vector>

#include "Token.hpp"
#include "../NodeType.h"
#include "Branchable.hpp"

namespace node
{
    class Node : public Branchable
    {
        public:
            Node(token::Token token = token::Token(), NodeType type = NTYPE_NONODE);
            virtual ~Node();

            virtual void add(Node node);

            virtual Node getNode(unsigned int index);

            virtual void print(std::string tabs);

        protected:
            token::Token token;

            NodeType type;

            std::vector<Node*> nodes;
    };

} /* namespace node */

#endif // NODE_H
