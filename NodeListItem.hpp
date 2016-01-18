#ifndef NODELISTITEM_HPP_INCLUDED
#define NODELISTITEM_HPP_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 16, 2015
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

namespace ast
{
    class SyntaxTree;
}

namespace parser
{
    class NodeListItem
    {
        public:
            NodeListItem();
            virtual ~NodeListItem() = 0;

            virtual SP<ast::SyntaxTree> format() = 0;
    };
}

#endif // NODELISTITEM_HPP_INCLUDED
