#ifndef BRANCHABLE_HPP_INCLUDED
#define BRANCHABLE_HPP_INCLUDED

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
    class Branchable
    {
        public:
            Branchable(WP<Branchable> root) :
                root(root)
            {

            }

            virtual void add(SP<ast::Branchable> n) = 0;

            virtual void print(std::string tabs) = 0;

            WP<Branchable> root;
    };
}

#endif // BRANCHABLE_HPP_INCLUDED
