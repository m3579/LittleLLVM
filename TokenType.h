#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

/*
 * TokenType.hpp
 *
 * /TheCompilerFramework/Headers/include/TokenType.hpp
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

#include <string>

typedef std::string TokenType;

#define createTokenType(name) const TokenType name = #name

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

createTokenType(TTYPE_NOTOKEN);
createTokenType(TTYPE_INVTOKEN);
createTokenType(TTYPE_OUTOFRANGE);
createTokenType(TTYPE_ERRORQUIT);

#pragma GCC diagnostic pop

#endif // TOKENTYPE_H_INCLUDED
