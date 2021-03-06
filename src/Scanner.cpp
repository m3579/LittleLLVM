/*
 * Scanner.cpp
 *
 * /TheCompilerFramework/Sources/src/Scanner.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 28, 2015
 *
 *      Purpose: The Scanner's job is to read characters from the source code and feed them to whoever is using the
 *               Scanner. In this compiler framework, that will usually and should only be the lexer.
 *
 *        Usage: Will usually be (and should only be) invoked by the lexer.
 *
 *        Notes:
 *
 */

// TODO: remove iostream includes from files that don't need it
#include <iostream>
#include <cstring>

#include "Scanner.hpp"

namespace scanner
{

	Scanner::Scanner(const char* sourceCode) :
        finished(false), sourceCodePointer(sourceCode), movementCounter(0)
	{
		currentChar = *sourceCodePointer;

		if (getCurrentChar() == '\0') {
			hasMore = false;
		}
		else {
			hasMore = true;
		}

		lineNumber = 1;
		columnNumber = 1;

		currentIndex = 0;
	}

	Scanner::~Scanner()
	{

	}

	const char Scanner::getCurrentChar()
	{
		return currentChar;
	}

	const char Scanner::moveToNextChar()
	{
		if (hasMoreSource()) {

			sourceCodePointer++;

			currentChar = *sourceCodePointer;

			columnNumber++;

			currentIndex++;

			if (fetchPreviousChar() == '\n') {
				lineNumber++;
				columnNumber = 1;
			}

            movementCounter++;

			if (currentChar == '\0') {
				hasMore = false;
			}

			return currentChar;

		}

		return '\0';
	}

	const char Scanner::fetchNextChar()
	{
		return *(sourceCodePointer + 1);
	}

	const char Scanner::fetchPreviousChar()
	{
		return *(sourceCodePointer - 1);
	}

	bool Scanner::hasMoreSource()
	{
		return hasMore;
	}

	int Scanner::getLineNumber()
	{
		return lineNumber;
	}

	int Scanner::getColumnNumber()
	{
		return columnNumber;
	}

	int Scanner::getCurrentIndex()
	{
		return currentIndex;
	}

	void Scanner::startCountingMovements()
	{
        movementCounter = 0;
        movementStartedColumnNumber = getColumnNumber();
        movementStartedLineNumber = getLineNumber();
	}

	void Scanner::reset()
	{
        for (int i = movementCounter; i > 0; i--) {

            sourceCodePointer--;
            currentChar = *sourceCodePointer;

            currentIndex--;
        }

        columnNumber = movementStartedColumnNumber;
        lineNumber = movementStartedLineNumber;
	}

} /* namespace scanner */

