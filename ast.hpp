#ifndef AST_HPP_INCLUDED
#define AST_HPP_INCLUDED

/*
 * ast.hpp
 *
 * /CompilerFrameworkInCPP/Headers/ast.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 19, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <functional>

#include "TokenManager.hpp"

namespace ast
{
    typedef std::function<void(parser::TokenManager&)> AstManipulationAction;

    extern AstManipulationAction symbolFoundDoNothing;
}

#endif // AST_HPP_INCLUDED
