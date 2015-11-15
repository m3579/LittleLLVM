#ifndef TOKEN_H
#define TOKEN_H

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
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

#include <string>
#include <map>

#include "../TokenType.h"

namespace token
{
    class Token
	{
        public:
            Token(int lineNumber = -1, int columnNumber = -1, std::string text = "",
                  TokenType type = TTYPE_NOTOKEN, std::string errorMessage = "");

            virtual ~Token();

            // Two methods for readability
            virtual bool isOfType(TokenType);
            virtual bool isNotOfType(TokenType);

            virtual std::string toString();

            virtual explicit operator bool() const;

            virtual Token& operator=(Token token);

            virtual int getLineNumber();
            virtual int getColumnNumber();

            virtual std::string getText();

            virtual TokenType getType();

            virtual std::string getErrorMessage();

            virtual void print(std::string tabs);

        protected:
            int lineNumber;
            int columnNumber;

            std::string text;

            TokenType type;

            std::string errorMessage;

	};
}

#endif // TOKEN_H_INCLUDED
