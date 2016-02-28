/*
 * Lexer.cpp
 *
 * /TheCompilerFramework/Sources/src/Lexer.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 28, 2015
 *
 *      Purpose: Converts the source code into tokens for the parser to assemble into an AST.
 *               The user will define what Tokens to generate by means of "tests", where the
 *               lexer will test for a particular type of token.
 *
 *        Usage: The user will supply the test functions. The Parser will use the lexer.
 *
 *        Notes:
 *
 */

#include <iostream>
#include <sstream>

#include "Lexer.hpp"
#include "Scanner.hpp"
#include "../utilities.h"

namespace lexer
{
	Lexer::Lexer(std::string sourceCode) :
		sourceCode(sourceCode), scanner(sourceCode.c_str())
	{

	}

	Lexer::~Lexer()
	{

	}

	token::Token Lexer::getNextToken()
	{
	    for (auto test = testFunctions.begin(); test != testFunctions.end(); ++test) {

            token::Token token = (*test)(scanner);

            if (token) {
                scanner.moveToNextChar();

                return token;
            }

        }

        return token::Token();
	}

	std::vector<token::Token> Lexer::tokenizeSource()
	{
		scanner::Scanner sc(sourceCode.c_str());

        std::vector<token::Token> tokens;

        bool lexing = true;

		while (lexing) {
            std::cout << "Iterating in lexer...\n";
            bool found = false;

            for (auto test = testFunctions.begin(); test != testFunctions.end(); ++test) {
                token::Token token( ((*test)(sc)) );

                if (token) {
                    found = true;
                    tokens.push_back(token);
                    sc.moveToNextChar();

                    if (sc.finished) {
                        lexing = false;
                        found = true;
                    }

                    break;
                }

            }

            if (!found) {
                std::stringstream error;
                error << "No test in lexer for |"
                      << sc.getCurrentChar()
                      << "| at line "
                      << sc.getLineNumber()
                      << " column "
                      << sc.getColumnNumber();

                utilities::logError(error.str());
            }
        }

		return tokens;

	}

	void Lexer::addTest(test test)
	{
	    testFunctions.push_back(test);
	}

} /* namespace lexer */
