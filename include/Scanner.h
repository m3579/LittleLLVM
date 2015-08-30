#ifndef SCANNER_H
#define SCANNER_H

/*
 * Filename.h
 *
 * /Project/Headers/include/Filename.h
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

namespace scanner
{
	class Scanner
	{
		public:
			Scanner(const char* sourceCodePointer);
			~Scanner();

			const char getCurrentChar();

			// Will update the currentChar variable; "moves" to the next char...
			const char moveToNextChar();

			// ...whereas these two don't update the currentChar variable. Subsequent calls to
			// fetchNext/PrevChar() will return the same character.
			const char fetchNextChar();
			const char fetchPreviousChar();

			bool hasMoreSource();

			int getLineNumber();
			int getColumnNumber();

			int getCurrentIndex();

		private:
			const char* sourceCodePointer;

			char currentChar;

			bool hasMore;

			int lineNumber;
			int columnNumber;

			int currentIndex;
	};
} /* namespace scanner */

#endif // SCANNER_H_INCLUDED
