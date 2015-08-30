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
#include <cstring>

#include "Scanner.h"

namespace scanner
{

	Scanner::Scanner(const char* sourceCode) :
		sourceCodePointer(sourceCode)
	{
		currentChar = *sourceCodePointer;

		if (fetchNextChar() == '\0') {
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

} /* namespace scanner */

