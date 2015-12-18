#ifndef PARSER_TEST_H_INCLUDED
#define PARSER_TEST_H_INCLUDED

/*
 * Filename.hpp
 *
 * /Project/Headers/include/Filename.hpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Aug 30, 2015
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <iostream>

#include "../TokenType.h"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace lexer;
using namespace token;
using namespace parser;
using namespace node;
using namespace ast;

createTokenType(TTYPE_NUMONE);
createTokenType(TTYPE_PLUS);
createTokenType(TTYPE_END);

createNodeType(NTYPE_NUMONE);
createNodeType(NTYPE_PLUS);
createNodeType(NTYPE_END);

using namespace lexer;
using namespace parser;

Token numberTest(scanner::Scanner& sc);
Token plusTest(scanner::Scanner& sc);
Token spaceTest(scanner::Scanner& sc);
Token endTest(scanner::Scanner& sc);

void noFind(TokenManager& tm);

void parserGo()
{
    Lexer lexer("1 + 1");

    lexer.addTest(numberTest);
    lexer.addTest(plusTest);
    lexer.addTest(spaceTest);
    lexer.addTest(endTest);

    Parser parser(lexer);

    std::shared_ptr<Symbol> startingSymbol(new Symbol(TTYPE_NUMONE, "Starting symbol", nullptr, NTYPE_NUMONE));
    parser.addSymbol(startingSymbol);

    std::shared_ptr<Symbol> plusSymbol(new Symbol(TTYPE_PLUS, "Plus Symbol", nullptr, NTYPE_PLUS));
    startingSymbol->addNextSymbol(plusSymbol, 1);

    std::shared_ptr<Symbol> finalSymbol(new Symbol(TTYPE_NUMONE, "Final Symbol", nullptr, NTYPE_NUMONE));
    plusSymbol->addNextSymbol(finalSymbol, -1);

    std::shared_ptr<Symbol> eolSymbol(new Symbol(TTYPE_END, "End", nullptr, NTYPE_END));
    finalSymbol->addNextSymbol(eolSymbol, 0);

    parser.noFind = noFind;

    std::shared_ptr<SyntaxTree> tree(parser.createSyntaxTree());

    tree->print("");

}

// 1 1 1 1 1
Token numberTest(scanner::Scanner& sc)
{
    if (sc.getCurrentChar() == '1') {
        return Token(sc.getLineNumber(), sc.getColumnNumber(), "1", TTYPE_NUMONE);
    }
    return Token();
}

// + + + + +
Token plusTest(scanner::Scanner& sc)
 {
    if (sc.getCurrentChar() == '+') {
        return Token(sc.getLineNumber(), sc.getColumnNumber(), "+", TTYPE_PLUS);
    }
    return Token();
}

// SPACE SPACE SPACE SPACE SPACE
Token spaceTest(scanner::Scanner& sc)
{
    if (sc.getCurrentChar() == ' ') {
        sc.moveToNextChar();
    }

    return Token();
}

// END END END END END
Token endTest(scanner::Scanner& sc)
{
    if (sc.getCurrentChar() == '\0') {
        sc.finished = true;
        return Token(sc.getLineNumber(), sc.getColumnNumber(), "\0", TTYPE_END);
    }
    return Token();
}

void noFind(TokenManager& tm)
{
    std::cout << "Error!";
    exit = true;
}

#endif // PARSER_TEST_H_INCLUDED
