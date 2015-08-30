#ifndef PARSER_TEST_H_INCLUDED
#define PARSER_TEST_H_INCLUDED

/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 30, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <iostream>

#include "../TokenType.h"
#include "Lexer.h"
#include "Parser.h"

createTokenType(TTYPE_NUMONE);
createTokenType(TTYPE_PLUS);
createTokenType(TTYPE_END);

createNodeType(NTYPE_NUMONE);
createNodeType(NTYPE_PLUS);
createNodeType(NTYPE_END);

using namespace lexer;
using namespace parser;

void parserGo()
{
    Lexer lexer("1 + 1");

    // 1 1 1 1 1
    lexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '1') {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "1", TTYPE_NUMONE);
            }
            return Token();
        }
    );

    // + + + + +
    lexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '+') {
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "+", TTYPE_PLUS);
            }
            return Token();
        }
    );

    // SPACE SPACE SPACE SPACE SPACE
    lexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == ' ') {
                sc.moveToNextChar();
            }

            return Token();
        }
    );

    // END END END END END
    lexer.addTest(
        [] (Scanner& sc)
        {
            if (sc.getCurrentChar() == '\0') {
                finished = true;
                return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TTYPE_END);
            }
            return Token();
        }
    );

    Parser parser(lexer);

    Terminal startingTerminal(TTYPE_NUMONE,
    [] (TokenManager& tm)
    {
        std::cout << "Found number 1\n";
        tm.moveToNextToken();
    },
                              NTYPE_NUMONE);

    parser.addTerminal(startingTerminal);

    Terminal plusTerminal(TTYPE_PLUS,
    [] (TokenManager& tm)
    {
        std::cout << "Found plus sign\n";
        tm.moveToNextToken();
    },
                          NTYPE_PLUS);

    startingTerminal.addTerminal(plusTerminal);

    Terminal finalTerminal(TTYPE_NUMONE,
    [] (TokenManager& tm)
    {
        std::cout << "Found final number 1\n";
        tm.moveToNextToken();
    },
                          NTYPE_NUMONE
    );

    plusTerminal.addTerminal(finalTerminal);

    Terminal endTerminal(TTYPE_END,
    [] (TokenManager& tm)
    {
        std::cout << "Found end\n";
    },
                         NTYPE_END
    );

    finalTerminal.addTerminal(endTerminal);

    SyntaxTree tree(parser.createSyntaxTree());

    tree.print("");

}

#endif // PARSER_TEST_H_INCLUDED
