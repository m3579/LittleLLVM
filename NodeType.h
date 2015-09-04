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
 *          The Different Types of Nodes and their Integer Values
 *
 *          You should only use the default Node constructor when a Node is simply not there. Any other time,
 *          try to use the arg constructor and set the type to another Node type (like Invalid node).
 *
 *          -1       No node
 *           0       Invalid node
 *           1       Statement
 *
 */

extern int ntypeNumber;

#define createNodeType(NAME) const int NAME = ++ntypeNumber

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

createNodeType(NTYPE_NONODE);
createNodeType(NTYPE_INVNODE);
createNodeType(NTYPE_STMT);

#pragma GCC diagnostic pop

#endif // NODETYPE_H_INCLUDED
