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
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        },
        "Starting terminal"
    );

    Terminal plusTerminal(TTYPE_PLUS,
        [] (TokenManager& tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_PLUS);
        },
        "Plus Terminal"
    );

    Terminal finalTerminal(TTYPE_NUMONE,
        [] (TokenManager& tm)
        {
            tm.moveToNextToken();

            return Node(tm.fetchPreviousToken(), NTYPE_NUMONE);
        },
        "Final Terminal"
    );

    Terminal endTerminal(TTYPE_END,
        [] (TokenManager& tm)
        {
            std::cout << "End\n";
            return Node(tm.fetchPreviousToken(), NTYPE_END);
        },
        "End"
    );
    startingTerminal.addTerminal(plusTerminal);
    plusTerminal.addTerminal(finalTerminal);

    finalTerminal.addTerminal(endTerminal);

    parser.addTerminal(startingTerminal);

    std::cout << "One: " << TTYPE_NUMONE << "\n"
              << "Plus: " << TTYPE_PLUS << "\n"
              << "End: " << TTYPE_END << "\n\n";

    SyntaxTree tree(parser.createSyntaxTree());

    // tree.print("");

}

#endif // PARSER_TEST_H_INCLUDED
