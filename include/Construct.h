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
#include "TreeForm.hpp"

namespace ast
{
    class Construct
    {
        public:
            Construct(std::vector<SP<Symbol>> symbols...);
            ~Construct();

            Construct setTreeForm(SP<TreeForm> treeForm);

        private:
            std::vector<SP<Symbol>> symbols;

            SP<TreeForm> treeForm;
    };
}

#endif // CONSTRUCT_H
