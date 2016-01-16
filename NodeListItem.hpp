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

#include "SyntaxTree.hpp"

namespace ast
{
    class NodeListItem
    {
        NodeListItem();
        virtual ~NodeListItem();

        virtual ast::SyntaxTree format() = 0;
    };
}


#endif // NODELISTITEM_HPP_INCLUDED
