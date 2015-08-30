#ifndef TOKENTYPE_H_INCLUDED
#define TOKENTYPE_H_INCLUDED

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

#define createTokenType(name) extern const int name = ++ttypeNumber

#endif // TOKENTYPE_H_INCLUDED
