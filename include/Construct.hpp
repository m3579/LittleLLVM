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

#ifndef CONSTRUCT_HPP
#define CONSTRUCT_HPP

#include <initializer_list>

#include "Symbol.hpp"
#include "TreeForm.hpp"

namespace ast
{
    class Construct
    {
        public:
            // TODO rename arguments tokenType and nodeType
            Construct(std::string name, TokenType tokenType, NodeType nodeType);
            Construct(std::string name, std::vector<SP<Construct>> constructs);
            ~Construct();

            Construct setTreeForm(SP<TreeForm> treeForm);

            bool isLeaf();
            bool isBranch();

            TokenType getTokenType();
            NodeType getNodeType();

            std::string getName();

            // TODO rename this
            std::vector<SP<Construct>> getComponents();

            // TODO shorten this method name
            void setActionAfterConstructNotFound(parser::TokenManager& tm);
            void noFind(parser::TokenManager& tm);

        private:
            bool containsOtherConstructs;

            std::vector<SP<Construct>> constructs;

            SP<TreeForm> treeForm;

            TokenType tokenType;
            NodeType nodeType;

            std::string name;

            AstManipulationAction noFindAction;
    };
}

#endif // CONSTRUCT_HPP
