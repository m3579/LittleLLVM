#ifndef NODETYPE_H_INCLUDED
#define NODETYPE_H_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 30, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <string>

typedef std::string NodeType;

#define createNodeType(name) const NodeType name = #name

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

createNodeType(NTYPE_NONODE);
createNodeType(NTYPE_INVNODE);
createNodeType(NTYPE_STMT);

#pragma GCC diagnostic pop

#endif // NODETYPE_H_INCLUDED
