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

#include "Branchable.hpp"
#include "Node.hpp"

namespace ast
{

    class SyntaxTree : public Branchable
    {
        public:
            SyntaxTree();
            virtual ~SyntaxTree();

            virtual void add(std::shared_ptr<node::Node> statement);

            virtual void print(std::string tabs);

            std::vector<std::shared_ptr<node::Node>> statements;

    };
} /* namespace ast */

#endif // SYNTAXTREE_H
