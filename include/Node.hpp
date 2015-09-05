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

namespace node
{

    class Node
    {
        public:
            Node(token::Token token = token::Token(), int type = -1);
            ~Node();

            void addNode(Node node);

            Node getNode(unsigned int index);

            void print(std::string tabs);

        private:
            token::Token token;

            int type;

            std::vector<Node> nodes;
    };

} /* namespace node */

#endif // NODE_H
