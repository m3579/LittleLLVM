/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
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

#include <iostream>

#include "SingleNodeListItem.hpp"

namespace parser
{
    SingleNodeListItem::SingleNodeListItem(token::Token token, NodeType nodeType) :
        token(token), nodeType(nodeType)
    {

    }

    SingleNodeListItem::~SingleNodeListItem()
    {

    }

    void SingleNodeListItem::print(std::string tabs)
    {
        std::cout << tabs << "Node:"
                  << tabs << "\t" << token.getText()
                  << "\n";
    }
}
