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

#include "Node.hpp"
#include "Token.hpp"
#include "../NodeType.h"
#include "SyntaxTreeComponent.hpp"
#include "SmartPointer.hpp"

using namespace pointer;

namespace node
{
    class Node : public ast::SyntaxTreeComponent
    {
        public:
            Node(token::Token token = token::Token(), NodeType type = NTYPE_NONODE);
            virtual ~Node();

            virtual void add(SP<ast::SyntaxTreeComponent> n);

            virtual SP<ast::SyntaxTreeComponent> getNode(unsigned int index);

            virtual void print(std::string tabs);

        protected:
            token::Token token;

            NodeType type;

            std::vector<SP<ast::SyntaxTreeComponent>> nodes;
    };

} /* namespace node */

#endif // NODE_H
