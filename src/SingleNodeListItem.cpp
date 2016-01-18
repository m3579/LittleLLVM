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

}
