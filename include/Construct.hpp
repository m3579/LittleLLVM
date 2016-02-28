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
            // TODO: make checks to make sure that the programmer does not list an optional Construct in a
            // treeForm
            // TODO: rename arguments tokenType and nodeType
            Construct(std::string name, TokenType tokenType, NodeType nodeType, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            Construct(std::string name, std::vector<TokenType> tokenTypes, std::vector<NodeType> nodeTypes, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            Construct(std::vector<SP<Construct>> constructs, std::string name, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            Construct(std::string name, std::vector<SP<Construct>> components, ActionAfterParserEvent found, ActionAfterParserEvent notFound);
            ~Construct();

            // TODO: make function to create copy of Construct shared pointer
            // (duplicate the memory so that the copy does not point to the
            // original object)

            bool isLeaf();
            bool isBranch();

            ActionAfterParserEvent found;
            ActionAfterParserEvent notFound;

            SP<ConstructTreeFormNode> treeForm;

            bool optional;

            std::vector<SP<Construct>> constructs;

            std::vector<SP<Construct>> components;

            std::vector<TokenType> tokenTypes;
            std::vector<NodeType> nodeTypes;

            std::string name;

        private:
            bool containsOtherConstructs;

    };
}

#endif // CONSTRUCT_HPP
