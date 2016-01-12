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
#include "Construct.h"

using namespace pointer;

namespace parser
{
    extern bool exit;

    class Parser
    {
        public:
            Parser(lexer::Lexer lexr);
            virtual ~Parser();

            virtual SP<ast::SyntaxTree> createSyntaxTree();

            virtual void addConstruct(SP<ast::Construct> construct);

            ast::AstManipulationAction noFind;

        protected:
            SP<ast::SyntaxTreeComponent> lookFor(SP<ast::Symbol> lookingFor, TokenManager& tm);

            lexer::Lexer lexr;

            std::vector<SP<ast::Construct>> symbols;
    };

} /* namespace parser */

#endif // PARSER_H
