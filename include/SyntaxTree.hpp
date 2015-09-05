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

#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "Node.hpp"

namespace ast
{

    class SyntaxTree
    {
        public:
            SyntaxTree();
            ~SyntaxTree();

            node::Node addStatement(node::Node statement);

            void print(std::string tabs);

        private:
            std::vector<node::Node> statements;

    };
} /* namespace ast */

#endif // SYNTAXTREE_H
