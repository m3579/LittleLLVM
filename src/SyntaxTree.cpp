/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "SyntaxTree.h"

namespace ast
{

    SyntaxTree:: SyntaxTree()
    {

    }

     SyntaxTree::~ SyntaxTree()
    {

    }

    Node SyntaxTree::addStatement(Node statement)
    {
        statements.push_back(statement);
        return statement;
    }

    void SyntaxTree::print(std::string tabs)
    {

    }

} /* namespace ast */
