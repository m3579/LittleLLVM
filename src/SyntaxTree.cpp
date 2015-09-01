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

#include <iostream>

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
        std::cout << "Syntax Tree:\n\n";
        for (auto it = statements.begin(); it != statements.end(); ++it) {
            it->print("\t");
        }
        std::cout << "\n\n";
    }

} /* namespace ast */
