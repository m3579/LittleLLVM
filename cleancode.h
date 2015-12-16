#ifndef CLEANCODE_H_INCLUDED
#define CLEANCODE_H_INCLUDED

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



#include "Lexer.hpp"

#ifdef __GNUC__
    #warning("Use of cleancode.h was deprecated after version 1 and is not recommended")
#elif defined(_MSC_VER)
    #pragma warning("Use of cleancode.h was deprecated after version 1 and is not recommended")
#else
    #pragma message("Use of cleancode.h was deprecated after version 1 and is not recommended")
#endif

#define test(sc) [] (scanner::Scanner& sc)

lexer::Lexer* __lexer;

#define setLexer(lexer) __lexer = &lexer

#define makeTest(scanner) __lexer->addTest(test(scanner)

#define endTest );


#define createSymbol(symbol) ast::Symbol symbol(

#define forTokenType(type) type,

#define withId(id)         id,

#define astAction(tokenManager) [] (parser::TokenManager& tokenManager)

#define endSymbol     );


#endif // CLEANCODE_H_INCLUDED
