#ifndef LEXER_H
#define LEXER_H

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


#include <vector>
#include <functional>

#include "Scanner.h"
#include "Token.h"

using namespace scanner;
using namespace token;

namespace lexer
{
    typedef Token (*testXxx)(Scanner&);

    extern bool finished;

	class Lexer
	{
		public:
			Lexer(std::string sourceCode, std::vector<testXxx> handlers);
			~Lexer();

            Token getNextToken();

			std::vector<Token> tokenizeSource();

			std::string sourceCode;

        private:
            std::vector<testXxx> testFunctions;

            Scanner scanner;

	};

} /* namespace lexer */

#endif // LEXER_H_INCLUDED
