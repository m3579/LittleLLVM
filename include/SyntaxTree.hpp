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

#ifndef SYNTAXTREE_HPP
#define SYNTAXTREE_HPP

#include "TokenManager.hpp"
#include "SyntaxTreeComponent.hpp"

namespace ast
{
    class SyntaxTree : public SyntaxTreeComponent
    {
        public:
            SyntaxTree();
            virtual ~SyntaxTree();

            virtual void add(SP<SyntaxTreeComponent> statement);

            virtual void print(std::string tabs);

            std::vector<SP<SyntaxTreeComponent>> statements;

    };

} /* namespace ast */

#endif // SYNTAXTREE_HPP
