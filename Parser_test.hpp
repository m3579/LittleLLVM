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
#include "cleancode.h"

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
            finished = true;
            return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TTYPE_END);
        }
        return Token();
    }
    endTest

    Parser parser(lexer);

    createTerminal(startingTerminal)
    forTokenType(TTYPE_NUMONE)
    withId("Starting terminal")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        }

    endTerminal

    parser.addTerminal(startingTerminal);

    createTerminal(plusTerminal)
    forTokenType(TTYPE_PLUS)
    withId("Plus Terminal")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_PLUS);
        }

    endTerminal

    startingTerminal.addNextTerminal(plusTerminal);

    createTerminal(finalTerminal)
    forTokenType(TTYPE_NUMONE)
    withId("Final Terminal")

        astAction(tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        }

    endTerminal

    plusTerminal.addNextTerminal(finalTerminal);

    createTerminal(eolTerminal)
    forTokenType(TTYPE_END)
    withId("End")

        astAction(tm)
        {
            return Node(tm.getCurrentToken(), NTYPE_END);
        }

    endTerminal

    finalTerminal.addNextTerminal(eolTerminal);

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
