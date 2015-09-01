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

        std::cout << "LEXER---\n";

        for (auto it = tokens.begin(); it != tokens.end(); ++it) {
            std::cout << it->getType() << " ";
        }
        std::cout << "\nLEXER---\n\n";

		return tokens;

	}

	void Lexer::addTest(testXxx test)
	{
	    testFunctions.push_back(test);
	}

} /* namespace lexer */
