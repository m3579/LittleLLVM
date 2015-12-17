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

namespace node
{
    class Node;
}

namespace ast
{
    class Branchable
    {
        public:
            Branchable(Branchable* root) :
                root(root) { }

            virtual void add(node::Node& node) = 0;

            Branchable* root;
    };
}

#endif // BRANCHABLE_HPP_INCLUDED
