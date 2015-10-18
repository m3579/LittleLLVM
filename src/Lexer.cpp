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

        return token::Token(0, 0, "", -1);
	}

	std::vector<token::Token> Lexer::tokenizeSource()
	{
		scanner::Scanner sc(sourceCode.c_str());

        std::vector<token::Token> tokens;

        bool lexing = true;

		while (lexing) {

            bool found = false;

            for (auto test = testFunctions.begin(); test != testFunctions.end(); ++test) {

                token::Token token( ((*test)(sc)) );

                if (sc.finished) {
                    lexing = false;
                    found = true;
                    break;
                }

                if (token) {
                    found = true;
                    tokens.push_back(token);
                    sc.moveToNextChar();
                    break;
                }

            }

            if (!found) {
                throw std::runtime_error(std::string("No test in lexer for |") + sc.getCurrentChar() + std::string("|"));
            }
        }

		return tokens;

	}

	void Lexer::addTest(test test)
	{
	    testFunctions.push_back(test);
	}

} /* namespace lexer */
