/*
 * Filename.cpp
 *
 * /Project/Sources/src/Filename.cpp
 *
 *       Author: Mihir Kasmalkar
 * Date created: Mon Da, Year
 *
 *      Purpose:
 *
 *        Usage:
 *
 *        Notes:
 *
 */

#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>

#include "Token.h"
#include "TokenManager.h"
#include "StampVersion.h"
#include "ErrorFunctions.h"

using namespace token;
using namespace error;

namespace parser
{
    TokenManager::TokenManager(std::vector<Token> tokens, Ref<Database> database) :
        tokens(tokens), currentTokenIndex(0), currentToken(tokens.at(currentTokenIndex)),
        database(database)

    {

    }

    TokenManager::~TokenManager()
    {

    }

    Token TokenManager::getCurrentToken()
    {
        return currentToken;
    }

    Token TokenManager::fetchNextToken()
    {
        return lookAhead(1);
    }

    Token TokenManager::fetchPreviousToken()
    {
        return lookBehind(1);
    }

    Token TokenManager::lookAhead(int spaces)
    {
        if (currentTokenIndex + spaces < tokens.size()) {
            return tokens.at(currentTokenIndex + spaces);
        }

        return tokens.back();
    }

    Token TokenManager::lookBehind(int spaces)
    {
        if (currentTokenIndex - spaces > 0) {
            return tokens.at(currentTokenIndex - spaces);
        }

        return tokens.front();
    }

    Token TokenManager::moveToNextToken()
    {
        if (currentTokenIndex + 1 < tokens.size()) {
            if (counting) {
                places++;
            }

            return (currentToken = tokens.at(++currentTokenIndex));
        }

        return tokens.back();
    }

    Token TokenManager::moveToPreviousToken()
    {
        if (currentTokenIndex - 1 > 0) {
            if (counting) {
                places--;
            }
            return (currentToken = tokens.at(--currentTokenIndex));
        }

        return tokens.front();
    }

    void TokenManager::startCounting()
    {
        counting = true;
        places = 0;
    }

    int TokenManager::stopCounting()
    {
        counting = false;
        return places;
    }

    void TokenManager::reset()
    {
        if (places > 0) {
            for (int i = 0; i < places; i++) {
                moveToPreviousToken();
            }
        }

        else if (places < 0) {
            for (int i = 0; i > places; i--) {
                moveToNextToken();
            }
        }

        stopCounting();
    }

    bool TokenManager::found(TokenType type)
    {
        if (getCurrentToken().getType() == type) {
            return true;
        }
        return false;
    }

    void TokenManager::consume(TokenType type)
    {
        //
        // When you call consume, you move TO that token, not PAST that token.
        // This is so that if you do something like this (which is done after almost every token in the parser):
        //
        // tm.consume(TokenType::XXX);
        // tm.moveToNextToken();
        //
        // whether or not a token of type XXX is there, you end up on the token after the whitespace/the previous token
        //
        if (fetchNextToken().getType() == type) {
            moveToNextToken();      // move to token
        }
    }

    void TokenManager::consumeWhitespace()
    {
        while (isWhitespace(fetchNextToken())) {
            consume(TokenType::WHITESPACE);
        }
    }

    Node TokenManager::getValue()
    {
        Node value;

// I use this macro repeatedly in this method
#define returnValue if (value.isValid()) return value

        value = getNumberValue();
        returnValue;

        value = getPin();
        returnValue;

        value = getLocation();
        returnValue;

        return Node(fetchNextToken(),
                    NodeType::NONODE);
    }

    // I use the Shunting Yard algorithm (https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
    // to convert expressions to postfix, then reverse the postfix expression
    // to get prefix. I then parse that into a Node.
    Node TokenManager::getNumberValue()
    {
        std::vector<Token> output;
        std::stack<Token>  opStack;

        Token topOp;

        // 0 = expecting an integer or left parenthesis
        // 1 = expecting an operator
        int next = 0;

        while (true) {

            Token token = getCurrentToken();

            if (isNumberValue(token)) {
                if (next != 0) {
                    logError(token, "I was expecting an operator here", true);
                }
                output.push_back(token);

                next = 1;
            }

            else if (isBinaryOperator(token)) {
                if (next != 1) {
                    if (token.getType() == TokenType::MINUS_SIGN) {
                        logError(token, "This value is either negative (not allowed) or WAY too big", true);
                    }
                    logError(token, "I was expecting a number or a left parenthesis here", true);
                }

                while (opStack.size() > 0
                       && ((topOp=opStack.top()).hasLowerPrecedence(token)
                           || topOp.hasEqualPrecedence(token))) {
                    opStack.pop();
                    output.push_back(topOp);
                }

                opStack.push(token);

                next = 0;

            }

            else if (token.isOfType(TokenType::LPAR)) {

                if (next != 0) {
                    logError(token, "I was expecting an operator here", true);
                }

                if (fetchNextToken().isOfType(TokenType::CREATE)) {
                    int IMPLEMENT_CREATE_STMT;  // TODO
                }

                opStack.push(token);

                next = 0;
            }

            else if (token.isOfType(TokenType::RPAR)) {

                if (next != 1) {
                    logError(token, "I was expecting a number or a left parenthesis here", true);
                }

                if (opStack.size() == 0) {
                    logError(token, "You have an extra right parenthesis here", true);
                }

                while (opStack.size() > 0
                       && ((topOp=opStack.top()).isNotOfType(TokenType::LPAR))) {
                    opStack.pop();
                    output.push_back(topOp);
                }

                if (opStack.size() == 0) {
                    logError(topOp, "You have an extra right parenthesis here", true);
                }

                opStack.pop();

                next = 1;

            }

            else {

                // This is not a number value
                if (output.size() == 0) {
                    return Node(token, NodeType::NONODE);
                }

                if (next == 0) {
                    logError(token, "You didn't finish this expression", true);
                }

                while (opStack.size() > 0) {
                    topOp = opStack.top();

                    if (topOp.isOfType(TokenType::RPAR)) {
                        logError(topOp, "You are missing a left parenthesis to match this right parenthesis", true);
                    }
                    else if (topOp.isOfType(TokenType::LPAR)) {
                        logError(topOp, "You are missing a right parenthesis to close this expression", true);
                    }

                    else {
                        opStack.pop();
                        output.push_back(topOp);
                    }
                }

                break;
            }

            consumeWhitespace();
            moveToNextToken();

        }

        // I should be one token AFTER the end of the expression
        // However, I need to be at the LAST token of the expression
        moveToPreviousToken();

        Node value(readUnit(output));

        return value;

    }

    Node TokenManager::getPin()
    {
        if (getCurrentToken().isOfType(TokenType::LEFTSQUAREBRACKET)) {
            if (fetchNextToken().isOfType(TokenType::IDENTIFIER)) {
                if (lookAhead(2).isOfType(TokenType::RIGHTSQUAREBRACKET)) {

                    Token pin = moveToNextToken();

                    // move to ] (last token in this expression)
                    moveToNextToken();

                    std::string pinText = pin.getText();

                    Node pinNode(pin, NodeType::PIN_LITERAL);

                    if (strstr("AllPins AllInputs AllOutputs \
                        UpperPins UpperInputs UpperOutputs \
                        LowerPins LowerInputs LowerOutputs \
                        SetAPins SetAInputs SetAOutputs \
                        SetBPins SetBInputs SetBOutputs \
                        SetCPins SetCInputs SetCOutputs \
                        SetDPins SetDInputs SetDOutputs \
                        Pin0 Pin1 Pin2 Pin3 Pin4 Pin5 Pin6 Pin7 Pin8 Pin9 Pin10 Pin11 Pin12 Pin 13 Pin14 Pin15 \
                        Input0 Input1 Input2 Input3 Input4 Input5 Input6 Input7 Input8 Input9 Input10 Input11 \
                        Input12 Input13 Input14 Input15 \
                        Output0 Output1 Output3 Output4 Output5 Output6 Output7 Output8 Output9 Output10 Output12 \
                        Output12 Output13 Output14 Output15", pinText.c_str()) == nullptr) {
                        logError(pin, "This is not a valid pin", true);
                    }

                    return pinNode;
                }
            }
        }

        return Node(getCurrentToken(), NodeType::NONODE);
    }

    Node TokenManager::getLocation()
    {
        // EEPROM
        Node location = getEEPROMLocation();
        if (location.isValid()) {
            return location;
        }

        // Scratch Pad RAM
        location = getSPRLocation();
        if (location.isValid()) {
            return location;
        }

        // No memory location
        return Node();

    }

    Node TokenManager::getEEPROMLocation()
    {
        Node location = getNumberValue();
        if (location.isValid()) {
            int value = calculateValue(location);

            if (value <= 2047) {
                Node node(location, NodeType::EEPLOCATION);
                return node;
            }
            else {
                logError(location, "Your EEPROM address is invalid (it has to be a location from 0 to 2047)", true);
            }
        }

        return Node();
    }

    Node TokenManager::getSPRLocation()
    {
        if (getCurrentToken().isOfType(TokenType::SPRLOCATION)) {
            consumeWhitespace();
            moveToNextToken();

            Token token = getCurrentToken();
            if (token.isOfType(TokenType::COLON)) {
                consumeWhitespace();
                moveToNextToken();

                Node value = getNumberValue();
                if (value.isValid()) {

                    if (calculateValue(value) > 127) {
                        logError(value, "Your Scratch Pad RAM address is invalid (it has to be a location from 0 to 126)", true);
                    }

                    Node node(value, NodeType::SPRLOCATION);
                    return node;
                }
                else {
                    logError(value, "You need to have a number value after \"SC:\"", true);
                }
            }
            else {
                logError(token, "You need to have a colon after SC", true);
            }

        }
        return Node();
    }

    // I use a vector reference because I need to pass the same vector to another function
    // (well...this function, recursively) and ALL copies of it need to be modified.
    Node TokenManager::readUnit(std::vector<Token>& tokens)
    {
        Token token = tokens.at(tokens.size() - 1);

        // I need to use this because some functions only take an iterator
        auto endIterator = tokens.end() - 1;

        if (isNumberValue(token)) {
            tokens.erase(endIterator);

            return Node(token, getNodeType(token.getType()));
        }
        else if (isBinaryOperator(token)) {

            tokens.erase(endIterator);

            Node value(token, getNodeType(token.getType()));
            value[SubnodeType::OPER2] = readUnit(tokens);
            value[SubnodeType::OPER1] = readUnit(tokens);

            return value;
        }
        else {
            return Node(token, NodeType::NONODE);
        }
    }

    std::vector<Token> TokenManager::getMatch(std::vector<isXxx> tests)
    {
        std::vector<Token> pattern;

        startCounting();

        for (unsigned int i = 0; i < tests.size(); i++) {
            isXxx testFunc = tests.at(i);

            Token token = fetchNextToken();

            // call test function on next token
            if ((this->*testFunc)(token)) {
                pattern.push_back(token);
                moveToNextToken();
                continue;
            }
            else {
                reset();
                // return empty vector
                return std::vector<Token> { };
            }
        }

        return pattern;

    }

    bool TokenManager::isDatatype(Token token)
    {
        switch(token.getType())
        {
            case TokenType::BIT:
            case TokenType::NIBBLE:
            case TokenType::BYTE:
            case TokenType::WORD:
            case TokenType::PIN:
                return true;

            default:
                return false;
        }
    }

    bool TokenManager::isNumberVariable(Token token)
    {
        if (isVariable(token)) {
            switch(database->getVariable(token.getText()).getType())
            {
                case DataType::NOTYPE:
                case DataType::NOVARIABLE:
                case DataType::PIN:
                    return false;

                default:
                    return true;
            }
        }

        // to stop compiler warnings about not returning a value
        return false;
    }

    bool TokenManager::isNumberValue(Token token)
    {
        switch(token.getType())
        {
            case TokenType::NUMBER_LITERAL:
                return true;

            case TokenType::IDENTIFIER: {
                if (isVariable(token)) {
                    if (isNumberVariable(token)) {
                        return true;
                    }
                }
            }

            default:
                return false;
        }
    }

    bool TokenManager::isVariable(Token token)
    {
        if (database->getVariable(token.getText()).getType() != DataType::NOVARIABLE) {
            return true;
        }
        return false;
    }

    bool TokenManager::isLiteral(Token token)
    {
        switch (token.getType())
        {
            case TokenType::NUMBER_LITERAL:
            case TokenType::STRING:
                return true;

            default:
                return false;
        }

    }

    bool TokenManager::isNumberLiteral(Token token)
    {
        switch (token.getType())
        {
            case TokenType::NUMBER_LITERAL:
                return true;

            default:
                return false;
        }

    }

    bool TokenManager::isSingleNumberValue(Token token)
    {
        if (database->getVariable(token.getText()).getType() != DataType::NOVARIABLE
            || token.getType() == TokenType::NUMBER_LITERAL) {
            return true;
        }

        return false;
    }

    bool TokenManager::isOperator(Token token)
    {
        switch (token.getType())
        {
            case TokenType::PLUS_SIGN:
            case TokenType::MINUS_SIGN:
            case TokenType::ASTERISK:
            case TokenType::FORWARD_SLASH:
            case TokenType::CARET:
            case TokenType::PERCENT:
            case TokenType::FRACTION_MULTIPLY:
                return true;

            default:
                return false;
        }
    }

    bool TokenManager::isUnaryOperator(Token token)
    {
        if (isOperator(token)) {
            switch(token.getType())
            {
                case TokenType::AMPERSAND:
                    return true;
                default:
                    return false;
            }
        }

        // to stop compiler warnings about not returning a value
        return false;
    }

    bool TokenManager::isBinaryOperator(Token token)
    {
        if (isOperator(token)) {
            switch(token.getType())
            {
                case TokenType::PLUS_SIGN:
                case TokenType::MINUS_SIGN:
                case TokenType::ASTERISK:
                case TokenType::FORWARD_SLASH:
                case TokenType::CARET:
                case TokenType::FRACTION_MULTIPLY:
                case TokenType::PERCENT:
                    return true;

                default:
                    return false;
            }
        }

        // To stop compiler warnings that I didn't return a value
        return false;
    }

    bool TokenManager::isExpression(std::vector<Token> tokens)
    {
        return true;
    }

    bool TokenManager::isValue(Token token)
    {
        if ( isDatatype(token)
            || isVariable(token)
            || isLiteral(token)
            || isExpression( std::vector<Token> { token } )
            ) {
                return true;
        }
        return false;
    }

    bool TokenManager::isWhitespace(Token token)
    {
        if (token.getType() == TokenType::WHITESPACE) {
            return true;
        }
        return false;
    }

    DataType TokenManager::inferType(Node node)
    {
        if (node.getType() == NodeType::PIN_LITERAL) {
            return DataType::PIN;
        }
        else if (node.getType() == NodeType::STRING) {
            return DataType::STRING;
        }
        else if (node.getType() == NodeType::ALIAS) {
            Alias alias = database->getAlias(node.getToken().getText());

            return alias.getType();
        }

        // it is a number
        int value = calculateValue(node);

        if (value < 0) {
            logError(node, "This value is either negative (not allowed) or WAY too big", true);
        }
        else if (value <= 1) {
            return DataType::BIT;
        }
        else if (value <= 15) {
            return DataType::NIBBLE;
        }
        else if (value <= 255) {
            return DataType::BYTE;
        }
        else if (value <= 65535) {
            return DataType::WORD;
        }
        else {
            logError(node, "The value of this expression is too large (specifically, larger than 65535)", true);
        }

        // to shut up compiler warnings
        return DataType::NOTYPE;
    }

    int TokenManager::calculateValue(Node node)
    {
        switch(node.getType())
        {
            case NodeType::NUMBER_LITERAL: {
                long long value = strtol(node.getToken().getText().c_str(), 0, 10);
                return value;
            }

            case NodeType::BIT:
            case NodeType::NIBBLE:
            case NodeType::BYTE:
            case NodeType::WORD:
            case NodeType::STRING:
            case NodeType::PIN:

            case NodeType::BIT_POINTER:
            case NodeType::NIBBLE_POINTER:
            case NodeType::BYTE_POINTER:
            case NodeType::WORD_POINTER:

            case NodeType::PIN_LITERAL:

            case NodeType::NOTYPE:
            case NodeType::NONODE:

            case NodeType::IDENTIFIER:
                return NAN;

            case NodeType::ALIAS: {
                Alias alias = database->getAlias(node.getToken().getText());

                return calculateValue(alias.getValue());
            }

            case NodeType::VARIABLE: {
                Variable var = database->getVariable(node.getToken().getText());

                return calculateValue(var.getValue());
            }

            case NodeType::ADD:
            case NodeType::ADD_ASSIGN:
                return calculateValue(node[SubnodeType::OPER1]) + calculateValue(node[SubnodeType::OPER2]);

            case NodeType::SUBTRACT:
            case NodeType::SUBTRACT_ASSIGN:
                return calculateValue(node[SubnodeType::OPER1]) - calculateValue(node[SubnodeType::OPER2]);

            case NodeType::MULTIPLY:
            case NodeType::MULTIPLY_ASSIGN:
                return calculateValue(node[SubnodeType::OPER1]) * calculateValue(node[SubnodeType::OPER2]);

            case NodeType::DIVIDE:
            case NodeType::DIVIDE_ASSIGN:
                return calculateValue(node[SubnodeType::OPER1]) / calculateValue(node[SubnodeType::OPER2]);

            case NodeType::MODULUS:
            case NodeType::MODULUS_ASSIGN:
                return calculateValue(node[SubnodeType::OPER1]) % calculateValue(node[SubnodeType::OPER2]);

            case NodeType::EXPONENT:
            case NodeType::EXPONENT_ASSIGN:
                return pow(calculateValue(node[SubnodeType::OPER1]), calculateValue(node[SubnodeType::OPER2]));

            case NodeType::FRACTION_MULTIPLY:
                return calculateValue(node[SubnodeType::OPER1]) * (calculateValue(node[SubnodeType::OPER2]) / 256);

            case NodeType::EEPLOCATION:
            case NodeType::SPRLOCATION:
                return calculateValue(node[SubnodeType::LOCATION]);
        }

        // to shut up compiler warnings
        return NAN;
    }

    NodeType TokenManager::getNodeType(TokenType type)
    {
        switch (type)
        {
            case TokenType::NUMBER_LITERAL:
                return NodeType::NUMBER_LITERAL;
            case TokenType::BIT:
                return NodeType::BIT;
            case TokenType::NIBBLE:
                return NodeType::NIBBLE;
            case TokenType::BYTE:
                return NodeType::BYTE;
            case TokenType::WORD:
                return NodeType::WORD;
            case TokenType::PIN:
                return NodeType::PIN;
            case TokenType::ALIASES:
                return NodeType::ALIAS;

            case TokenType::PLUS_SIGN:
                return NodeType::ADD;
            case TokenType::MINUS_SIGN:
                return NodeType::SUBTRACT;
            case TokenType::ASTERISK:
                return NodeType::MULTIPLY;
            case TokenType::FORWARD_SLASH:
                return NodeType::DIVIDE;
            case TokenType::PERCENT:
                return NodeType::MODULUS;
            case TokenType::CARET:
                return NodeType::EXPONENT;
            case TokenType::FRACTION_MULTIPLY:
                return NodeType::FRACTION_MULTIPLY;

            default:
                return NodeType::NONODE;
        }
    }

    NodeType TokenManager::getNodeType(DataType type)
    {
        switch(type)
        {
            case DataType::BIT:
                return NodeType::BIT;
            case DataType::NIBBLE:
                return NodeType::NIBBLE;
            case DataType::BYTE:
                return NodeType::BYTE;
            case DataType::WORD:
                return NodeType::WORD;
            case DataType::STRING:
                return NodeType::STRING;
            case DataType::ALIAS:
                return NodeType::ALIAS;

            default:
                return NodeType::NOTYPE;
        }
    }

    NodeType TokenManager::getPointerType(TokenType type)
    {
        switch(type)
        {
            case TokenType::BIT:
                return NodeType::BIT_POINTER;
            case TokenType::NIBBLE:
                return NodeType::NIBBLE_POINTER;
            case TokenType::BYTE:
                return NodeType::BYTE_POINTER;
            case TokenType::WORD:
                return NodeType::WORD_POINTER;

            default:
                return NodeType::NOTYPE;
        }

    }

    DataType TokenManager::getDataType(Node node)
    {
        switch(node.getType())
        {
            case NodeType::BIT:
                return DataType::BIT;

            case NodeType::NIBBLE:
                return DataType::NIBBLE;

            case NodeType::BYTE:
                return DataType::BYTE;

            case NodeType::WORD:
                return DataType::WORD;

            case NodeType::PIN:
                return DataType::PIN;

            case NodeType::STRING:
                return DataType::STRING;

            case NodeType::NUMBER_LITERAL:
                return inferType(node);

            default:
                return inferType(node);
        }
    }

    Location TokenManager::getLocationObject(Node node)
    {
        int location = strtol(node.getToken().getText().c_str(), NULL, 10);

        LocationType type = (node[SubnodeType::LOCATION].getType() == NodeType::EEPLOCATION)
                                ? LocationType::EEPROM : LocationType::SPRLOCATION;

        return Location(location, type);
    }
}
