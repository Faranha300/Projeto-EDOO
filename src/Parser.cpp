#include "Parser.h"
#include "Value.h"
#include <iostream>
#include <stdbool.h>
using namespace std;

void Parser::nextToken() {
    currentToken = tokenizer.getNextToken();
    //cout << "Token: " << currentToken.value << endl;
}

Parser::Parser(const string& expression) : tokenizer(expression) {
    nextToken();
}

Value Parser::parseOrExp() {
    Value value = parseAndExp();
    while (currentToken.value == "||") {
        nextToken();
        Value nextVal = parseAndExp();
        value = Value(value.asBool() || nextVal.asBool());
    }
    return value;
}

Value Parser::parseAndExp() {
    Value value = parseEqExp();
    while (currentToken.value == "&&") {
        nextToken();
        Value nextVal = parseEqExp();
        value = Value(value.asBool() && nextVal.asBool());
    }
    return value;
}

Value Parser::parseEqExp() {
    Value left = parseRelExp();
    while (currentToken.value == "==" || currentToken.value == "!=") {
        string op = currentToken.value;
        nextToken();
        Value right = parseRelExp();
        if (op == "==") {
            left = Value(left.asBool() == right.asBool());
        } else {
            left = Value(left.asBool() != right.asBool());
        }
    }
    return left;
}

Value Parser::parseRelExp() {
    Value left = parseAddExp();
    if (currentToken.value == "<" || currentToken.value == ">" ||
        currentToken.value == "<=" || currentToken.value == ">=") {
        string op = currentToken.value;
        nextToken();
        Value right = parseAddExp();
    
        int leftInt = left.asInt();
        int rightInt = right.asInt();
        if (op == "<") return leftInt < rightInt;
        if (op == ">") return leftInt > rightInt;
        if (op == "<=") return leftInt <= rightInt;
        if (op == ">=") return leftInt >= rightInt;
        throw runtime_error("error");
    }
    return left;
}


Value Parser::parseAddExp() {
    Value value = parseMulExp();
    while (currentToken.value == "+" || currentToken.value == "-") {
        string op = currentToken.value;
        nextToken();
        Value nextVal = parseMulExp();
        value = (op == "+") ? value.asInt() + nextVal.asInt() : value.asInt() - nextVal.asInt();
    }
    return value;
}

Value Parser::parseMulExp() {
    Value value = parseUnaryExp();
    while (currentToken.value == "*" || currentToken.value == "/") {
        string op = currentToken.value;
        nextToken();
        Value nextVal = parseUnaryExp();
        value = (op == "*") ? value.asInt() * nextVal.asInt() : value.asInt() / nextVal.asInt();
    }
    return value;
}

Value Parser::parseUnaryExp() {
    if (currentToken.value == "-") {
        nextToken();
        Value value = parseUnaryExp();
        if (value.asInt()) {
            return Value(-value.asInt());
        } else {
            throw runtime_error("error");
        }
    }
    return parsePrimaryExp();
}

Value Parser::parsePrimaryExp() {
    if (currentToken.value == "(") {
        nextToken();
        Value value = parseOrExp();
        if (currentToken.value != ")") throw runtime_error("error");
        nextToken();
        return value;
    }
    if (currentToken.type == TokenType::INTEGER) {
        int value = stoi(currentToken.value);
        nextToken();
        return Value(value);
    } 
    if (currentToken.type == TokenType::BOOLEAN) {
        if (currentToken.value == "true") {
            nextToken();
            return Value(true);
        } else if (currentToken.value == "false") {
            nextToken();
            return Value(false);
        }
    }
    throw runtime_error("error");
}

string Parser::evaluate() {
    try {
        Value result = parseOrExp();
        if (currentToken.type != TokenType::END) throw runtime_error("error");
        return result.isBoolean() ? (result.asBool() ? "true" : "false") : to_string(result.asInt());
    } catch (...) {
        return "error";
    }
}