#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

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
 *          The Different Types Of Tokens and their Integer Values
 *
 *          You should only use the default Token constructor when a Token is simply not there. Any other time,
 *          try to use the arg constructor and set the type to another Token type (like Invalid token).
 *
 *          -1      No Token
 *          0       Invalid token
 *
 */

extern int ttypeNumber;

#define createTokenType(name) const int name = ++ttypeNumber

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

createTokenType(TTYPE_NOTOKEN);
createTokenType(TTYPE_INVTOKEN);
createTokenType(TTYPE_OUTOFRANGE);
createTokenType(TTYPE_ERRORQUIT);

#pragma GCC diagnostic pop

#endif // TOKENTYPE_H_INCLUDED
