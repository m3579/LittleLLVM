#ifndef LEXER_H
#define LEXER_H

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


#include <vector>

#include "Scanner.hpp"
#include "Token.hpp"
#include "../TokenType.h"

namespace lexer
{
    typedef token::Token (*test)(scanner::Scanner&);

	class Lexer
	{
		public:
			Lexer(std::string sourceCode);
			virtual ~Lexer();

            virtual token::Token getNextToken();

			virtual std::vector<token::Token> tokenizeSource();

            virtual void addTest(test testFunction);

			std::string sourceCode;

        protected:
            std::vector<test> testFunctions;

            scanner::Scanner scanner;

	};

} /* namespace lexer */

#endif // LEXER_H_INCLUDED
