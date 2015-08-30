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

#include <sstream>
#include <iostream>

#include "Token.h"

#define NULLTOKENWARNING "You should usually not use the no-arg constructor for Tokens"

namespace token
{
	Token::Token(int ln, int cn, std::string text, int type) :
		lineNumber(ln), columnNumber(cn), text(text), type(type)
	{

	}

	bool Token::isOfType(int type)
	{
	    return this->type == type;
	}

	bool Token::isNotOfType(int type)
	{
	    return this->type != type;
	}

	std::string Token::toString()
	{
		std::stringstream summary;
		summary << "Token: |" << text << "|";
		summary << "\n\tType: " << type;
		summary << "\n\tAt: " << lineNumber;
		summary << " on " << columnNumber;

		return summary.str();
	}

	Token::operator bool() const
	{
		return type != -1;
	}

    Token& Token::operator=(Token token)
    {
        lineNumber = token.lineNumber;
        columnNumber = token.columnNumber;
        text = token.text;
        type = token.type;

        return *this;
    }

    int Token::getLineNumber()
	{
		return lineNumber;
	}

    int Token::getColumnNumber()
	{
		return columnNumber;
	}

    std::string Token::getText()
	{
		return text;
	}

    int Token::getType()
	{
		return type;
	}

	void Token::print(std::string tabs)
	{
        std::stringstream output;
        output << tabs << "Token: " << text << "\n";
        output << tabs << "\tType: " << type << "\n";
        output << tabs << "\tLine number: " << lineNumber << "\n";
        output << tabs << "\tColumn Number: " << columnNumber << "\n";

        std::cout << output.str() << "\n";
    }
} /* namespace token */
