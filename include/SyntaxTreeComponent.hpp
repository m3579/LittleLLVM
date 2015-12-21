#ifndef SyntaxTreeComponent_HPP_INCLUDED
#define SyntaxTreeComponent_HPP_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 15, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "SmartPointer.hpp"

using namespace pointer;

namespace node
{
    class Node;
}

namespace ast
{
    class Symbol;
}

namespace ast
{
    class SyntaxTreeComponent
    {
        public:
            SyntaxTreeComponent(WP<SyntaxTreeComponent> root) :
                root(root) { }

            virtual void add(SP<ast::SyntaxTreeComponent> n) = 0;

            virtual void print(std::string tabs) = 0;

            WP<SyntaxTreeComponent> getRoot()
            {
                return root;
            }

        private:
            WP<SyntaxTreeComponent> root;
    };
}

#endif // SyntaxTreeComponent_HPP_INCLUDED
