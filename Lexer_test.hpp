#ifndef LEXER_TEST_H_INCLUDED
#define LEXER_TEST_H_INCLUDED

/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 28, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include "Lexer.h"

using namespace lexer;

Token testHi(Scanner& sc);

void lexerGo()
{
    Lexer lexr("Hi");
    lexr.addTest(testHi);

    std::vector<Token> tokens(lexr.tokenizeSource());

    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        it->print("");
    }
}

Token testHi(Scanner& sc)
{
    if (sc.getCurrentChar() == 'H') {
        if (sc.moveToNextChar() == 'i') {
            finished = true;
            return Token(sc.getLineNumber(), sc.getColumnNumber(), "Hi", 1);
        }
    }

    return Token();
}


#endif // LEXER_TEST_H_INCLUDED
