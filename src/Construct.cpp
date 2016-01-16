/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Dec 21, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <cstdarg>

#include "Construct.h"

namespace ast
{
    Construct::Construct(std::vector<SP<Symbol>> symbols) :
        symbols(symbols)
    {

    }

    Construct::~Construct()
    {

    }
}
