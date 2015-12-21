/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <initializer_list>

#include "Symbol.hpp"

namespace ast
{
    class Construct
    {
        public:
            Construct(std::initializer_list<Symbol> symbols);
            ~Construct();

            Construct setTreeForm(Branch treeForm);

        private:
            std::vector<Symbol> symbols;

            Branch treeForm;
    };
}

#endif // CONSTRUCT_H
