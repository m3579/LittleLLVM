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
            Construct(std::string name, TokenType tokenType, NodeType nodeType, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional);
            Construct(std::string name, std::vector<TokenType> tokenTypes, std::vector<NodeType> nodeTypes, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional);
            Construct(std::string name, std::vector<SP<Construct>> constructs, ActionAfterParserEvent found, ActionAfterParserEvent notFound, bool optional);
            ~Construct();

            Construct setTreeForm(SP<ConstructTreeFormNode> treeForm);

            bool isLeaf();
            bool isBranch();

            std::vector<TokenType> getTokenTypes();
            std::vector<NodeType> getNodeTypes();

            std::string getName();

            // TODO: rename this
            std::vector<SP<Construct>> getComponents();

            ActionAfterParserEvent found;
            ActionAfterParserEvent notFound;

            SP<ConstructTreeFormNode> treeForm;

            bool isOptional();

        private:
            bool containsOtherConstructs;

            bool optional;

            std::vector<SP<Construct>> constructs;

            std::vector<TokenType> tokenTypes;
            std::vector<NodeType> nodeTypes;

            std::string name;
    };
}

#endif // CONSTRUCT_HPP
