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
            SyntaxTreeComponent() { };
            virtual ~SyntaxTreeComponent() { };

            virtual void add(SP<ast::SyntaxTreeComponent> c) = 0;

            virtual void print(std::string tabs) = 0;
    };
}

#endif // SyntaxTreeComponent_HPP_INCLUDED
