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

#include "Lexer.hpp"
#include "Scanner.hpp"

namespace lexer
{
     bool finished = false;

	Lexer::Lexer(std::string sourceCode) :
		sourceCode(sourceCode), scanner(sourceCode.c_str())
	{

	}

	Lexer::~Lexer()
	{

	}

	Token Lexer::getNextToken()
	{
	    for (auto test = testFunctions.begin(); test != testFunctions.end(); ++test) {

            Token token = (*test)(scanner);

            if (token) {
                scanner.moveToNextChar();

                return token;
            }

        }

        return Token(0, 0, "", -1);
	}

	std::vector<Token> Lexer::tokenizeSource()
	{
		Scanner sc(sourceCode.c_str());

        std::vector<Token> tokens;

        bool lexing = true;

		while (lexing) {
            for (auto test = testFunctions.begin(); test != testFunctions.end(); ++test) {

                Token token = (*test)(sc);

                if (token) {
                    tokens.push_back(token);

                    sc.moveToNextChar();

                    if (finished) {
                        lexing = false;
                        break;
                    }
                }

            }
		}

		return tokens;

	}

	void Lexer::addTest(test test)
	{
	    testFunctions.push_back(test);
	}

} /* namespace lexer */
