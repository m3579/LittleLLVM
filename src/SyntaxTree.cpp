/*
 * SyntaxTree.cpp
 *
 * /Project/Sources/src/SyntaxTree.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 29, 2015
 *
 *      Purpose: A SyntaxTree represents the AST (or CST if you want to use it that way) of the source code.
 *
 *        Usage: Will be created by the Parser and used to generate code/interpret and execute the source code
 *               by the code generator.
 *
 *        Notes:
 *
 */

#include <iostream>
#include <functional>

#include "SyntaxTree.hpp"

namespace ast
{
    std::function<void(parser::TokenManager&)> emptyAstAction;

    SyntaxTree:: SyntaxTree()
    {

    }

    SyntaxTree::~ SyntaxTree()
    {

    }

    void SyntaxTree::add(SP<ast::SyntaxTreeComponent> statement)
    {
        statements.push_back(statement);
    }

    void SyntaxTree::print(std::string tabs)
    {
        std::cout << tabs << "Syntax Tree:\n\n";

        for (auto it = statements.begin(); it != statements.end(); ++it) {
            (*it)->print(tabs + "\t");
        }

        std::cout << "\n\n";
    }

} /* namespace ast */
