#ifndef TOKEN_H
#define TOKEN_H

/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
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

namespace token
{
    class Token
	{
        public:
            Token();
            Token(int lineNumber, int columnNumber, std::string text, int type);

            // Two methods for readability
            bool isOfType(int);
            bool isNotOfType(int);

            std::string toString();

            explicit operator bool() const;

            Token& operator=(Token token);

            int getLineNumber();
            int getColumnNumber();

            std::string getText();

            int getType();

            std::string getErrorMessage();

            void print(std::string tabs);

        private:
            int lineNumber;
            int columnNumber;

            std::string text;

            int type;

	};
}

#endif // TOKEN_H_INCLUDED
