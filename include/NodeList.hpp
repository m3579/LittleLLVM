/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Jan 16, 2016
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#ifndef NODELIST_HPP
#define NODELIST_HPP

#include "NodeListItem.hpp"
#include "SingleNodeListItem.hpp"

namespace parser
{
    class NodeList : public NodeListItem
    {
        public:
            NodeList();
            ~NodeList();

            void addNode(SP<SingleNodeListItem> node);
            void addNodeList(SP<NodeList> nodeList);

            SP<ast::SyntaxTree> format();

        private:
            std::vector<SP<NodeListItem>> nodes;
    };
}

#endif // NODELIST_HPP
