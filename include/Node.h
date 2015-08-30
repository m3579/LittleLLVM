/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
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

#include "Token.h"

using namespace token;

namespace node
{

    class Node
    {
        public:
            Node();
            Node(Token token, int type);
            ~Node();

            void addNode(Node node);

            Node getNode(unsigned int index);

        private:
            Token token;

            int type;

            std::vector<Node> nodes;
    };

} /* namespace node */

#endif // NODE_H
