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

    extern bool finished;

	class Lexer
	{
		public:
			Lexer(std::string sourceCode);
			~Lexer();

            token::Token getNextToken();

			std::vector<token::Token> tokenizeSource();

            void addTest(test testFunction);

			std::string sourceCode;

        private:
            std::vector<test> testFunctions;

            scanner::Scanner scanner;

	};

} /* namespace lexer */

#endif // LEXER_H_INCLUDED
