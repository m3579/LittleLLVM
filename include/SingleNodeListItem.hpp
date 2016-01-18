/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 17, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#ifndef SINGLENODELISTITEM_HPP
#define SINGLENODELISTITEM_HPP

#include "Node.hpp"
#include "NodeListItem.hpp"

namespace parser
{
    class SingleNodeListItem : public NodeListItem
    {
        public:
            SingleNodeListItem(token::Token token, NodeType nodeType);
            virtual ~SingleNodeListItem();

            virtual SP<ast::SyntaxTree> format();

        private:
            token::Token token;
            NodeType nodeType;
    };

}

#endif // SINGLENODELISTITEM_HPP
