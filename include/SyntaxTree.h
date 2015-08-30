/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
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

#include "Node.h"

using namespace node;

namespace ast
{

    class SyntaxTree
    {
        public:
            SyntaxTree();
            ~SyntaxTree();

            void addStatement(Node node);

        private:
            std::vector<Node> statements;

    };
} /* namespace ast */

#endif // SYNTAXTREE_H
