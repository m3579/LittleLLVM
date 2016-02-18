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
#include "FlatNodeListItem.hpp"

namespace parser
{
    class FlatNode : public FlatNodeListItem
    {
        public:
            FlatNode(std::string name, token::Token token, NodeType nodeType);
            virtual ~FlatNode();

            void print(std::string tabs);

            bool isLeaf();

            std::string getName();

            token::Token getToken();

            NodeType getNodeType();

        private:
            token::Token token;
            NodeType nodeType;

            std::string name;
    };

}

#endif // SINGLENODELISTITEM_HPP
