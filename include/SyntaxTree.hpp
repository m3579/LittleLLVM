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

#include "TokenManager.hpp"
#include "SyntaxTreeComponent.hpp"
#include "Node.hpp"

namespace ast
{
    class SyntaxTree : public SyntaxTreeComponent
    {
        public:
            SyntaxTree();
            virtual ~SyntaxTree();

            virtual void add(SP<ast::SyntaxTreeComponent> statement);

            virtual void print(std::string tabs);

            std::vector<SP<ast::SyntaxTreeComponent>> statements;

    };
} /* namespace ast */

#endif // SYNTAXTREE_H
