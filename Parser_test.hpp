#ifndef PARSER_TEST_H_INCLUDED
#define PARSER_TEST_H_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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
#include "Lexer.hpp"
#include "Parser.hpp"
#include "cleancode.h"

using namespace lexer;
using namespace token;
using namespace parser;
using namespace node;
using namespace ast;

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

    setLexer(lexer);

    // 1 1 1 1 1
    makeTest(sc)
    {
        if (sc.getCurrentChar() == '1') {
            return Token(sc.getLineNumber(), sc.getColumnNumber(), "1", TTYPE_NUMONE);
        }
        return Token();
    }
    endTest

    // + + + + +
    makeTest(sc)
    {
        if (sc.getCurrentChar() == '+') {
            return Token(sc.getLineNumber(), sc.getColumnNumber(), "+", TTYPE_PLUS);
        }
        return Token();
    }
    endTest

    // SPACE SPACE SPACE SPACE SPACE
    makeTest(sc)
    {
        if (sc.getCurrentChar() == ' ') {
                sc.moveToNextChar();
        }

        return Token();
    }
    endTest

    // END END END END END
    makeTest(sc)
    {
        if (sc.getCurrentChar() == '\0') {
            sc.finished = true;
            return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TTYPE_END);
        }
        return Token();
    }
    endTest

    Parser parser(lexer);

    createSymbol(startingSymbol)
    forTokenType(TTYPE_NUMONE)
    withId("Starting terminal")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        }

    endSymbol

    parser.addSymbol(startingSymbol);

    createSymbol(plusSymbol)
    forTokenType(TTYPE_PLUS)
    withId("Plus Symbol")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_PLUS);
        }

    endSymbol

    startingSymbol.addNextSymbol(plusSymbol);

    createSymbol(finalSymbol)
    forTokenType(TTYPE_NUMONE)
    withId("Final Symbol")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        }

    endSymbol

    plusSymbol.addNextSymbol(finalSymbol);

    createSymbol(eolSymbol)
    forTokenType(TTYPE_END)
    withId("End")

        astAction(tm)
        {
            return Node(tm.getCurrentToken(), NTYPE_END);
        }

    endSymbol

    finalSymbol.addNextSymbol(eolSymbol);

    parser.noFind =
        astAction(tm)
        {
            std::cout << "Error!";
            exit = true;

            return Node();
        };

    SyntaxTree tree(parser.createSyntaxTree());

    tree.print("");

}

#endif // PARSER_TEST_H_INCLUDED
