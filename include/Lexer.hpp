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

using namespace scanner;
using namespace token;

namespace lexer
{
    typedef Token (*test)(Scanner&);

    extern bool finished;

	class Lexer
	{
		public:
			Lexer(std::string sourceCode);
			~Lexer();

            Token getNextToken();

			std::vector<Token> tokenizeSource();

            void addTest(test testFunction);

			std::string sourceCode;

        private:
            std::vector<test> testFunctions;

            Scanner scanner;

	};

} /* namespace lexer */

#endif // LEXER_H_INCLUDED
