/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "SyntaxTreeComponent.hpp"
#include "SyntaxTree.hpp"
#include "Lexer.hpp"
#include "Symbol.hpp"
#include "TokenManager.hpp"
#include "NodeType.h"
#include "SmartPointer.hpp"
#include "Construct.hpp"
#include "FlatNodeList.hpp"

using namespace pointer;

namespace parser
{
    // TODO add else clause for loop in parser that handles return values of type RecursiveSearchResult
    extern bool exit;

    enum class RecursiveSearchResult {
        NOTFOUND, NOTFOUNDALREADYHANDLED, FINISHED
    };

    class Parser
    {
        public:
            Parser(lexer::Lexer lexr);
            virtual ~Parser();

            // TODO remove/rethink all of these `virtual`s
            virtual SP<ast::SyntaxTree> createSyntaxTree();

            virtual void addConstruct(SP<ast::Construct> construct);

            ast::ActionAfterParserEvent notFound;

        protected:
            virtual RecursiveSearchResult lookFor(SP<ast::Construct> c, SP<parser::FlatNodeList> nodeList, TokenManager& tm);

            virtual SP<ast::SyntaxTree> assembleSyntaxTree(std::vector<SP<parser::FlatNodeList>> statements);

            void assembleSyntaxTreeBranch(SP<ast::ConstructTreeFormNode> treeFormNode, SP<node::Node> rootNode, std::vector<SP<FlatNode>> flatNodePool);

            SP<FlatNode> findMatchingFlatNode(SP<ast::ConstructTreeFormNode> constructTreeFormNode, std::vector<SP<FlatNode>> flatNodePool);

            lexer::Lexer lexr;

            std::vector<SP<ast::Construct>> constructs;
    };

} /* namespace parser */

#endif // PARSER_H
