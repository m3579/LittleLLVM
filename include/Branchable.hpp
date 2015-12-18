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

#include <memory>

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
            Branchable(std::shared_ptr<Branchable> root) :
                root(root) { }

            virtual void add(std::shared_ptr<node::Node> n) = 0;

            virtual void print(std::string tabs) = 0;

            std::shared_ptr<Branchable> root;
    };
}

#endif // BRANCHABLE_HPP_INCLUDED
