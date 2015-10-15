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

namespace token
{
    class Token
	{
        public:
            Token(int lineNumber = -1, int columnNumber = -1, std::string text = "", int type = -1);
            virtual ~Token();

            // Two methods for readability
            virtual bool isOfType(int);
            virtual bool isNotOfType(int);

            virtual std::string toString();

            virtual explicit operator bool() const;

            virtual Token& operator=(Token token);

            virtual int getLineNumber();
            virtual int getColumnNumber();

            virtual std::string getText();

            virtual int getType();

            virtual void print(std::string tabs);

            bool poisoned;

        protected:
            int lineNumber;
            int columnNumber;

            std::string text;

            int type;

	};
}

#endif // TOKEN_H_INCLUDED
