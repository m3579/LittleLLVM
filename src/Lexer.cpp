/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
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

#include <iostream>

#include "Lexer.h"
#include "Scanner.h"

namespace lexer
{
    bool finished = false;

	Lexer::Lexer(std::string sourceCode, std::vector<testXxx> testFunctions) :
		sourceCode(sourceCode), testFunctions(testFunctions), scanner(sourceCode.c_str())
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

} /* namespace lexer */
