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
#include "ConstructTreeFormNode.hpp"

namespace ast
{
    class Construct
    {
        public:
            // TODO rename arguments tokenType and nodeType
            Construct(std::string name, TokenType tokenType, NodeType nodeType, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            Construct(std::string name, std::vector<SP<Construct>> constructs, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            ~Construct();

            Construct setTreeForm(SP<ConstructTreeFormNode> treeForm);

            bool isLeaf();
            bool isBranch();

            TokenType getTokenType();
            NodeType getNodeType();

            std::string getName();

            // TODO: rename this
            std::vector<SP<Construct>> getComponents();

            ActionAfterParserEvent found;
            ActionAfterParserEvent notFound;

            SP<ConstructTreeFormNode> treeForm;

        private:
            bool containsOtherConstructs;

            std::vector<SP<Construct>> constructs;

            TokenType tokenType;
            NodeType nodeType;

            std::string name;
    };
}

#endif // CONSTRUCT_HPP
