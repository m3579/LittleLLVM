#ifndef CLEANCODE_H_INCLUDED
#define CLEANCODE_H_INCLUDED

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

#include "Lexer.h"


#define test(scanner) [] (Scanner& scanner)

lexer::Lexer* __lexer;

#define setLexer(lexer) __lexer = &lexer

#define makeTest(scanner) __lexer->addTest(test(scanner)

#define endTest );


#define createTerminal(terminal) Terminal terminal(

#define forTokenType(type) type,

#define withId(id)         id,

#define astAction(tokenManager) [] (TokenManager& tokenManager)

#define endTerminal     );


#endif // CLEANCODE_H_INCLUDED
