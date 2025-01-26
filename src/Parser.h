#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Value.h"
#include <stdexcept>
#include <string>
using namespace std;

class Parser {
private:
    Tokenizer tokenizer;
    Token currentToken;

    void nextToken();
    Value parseOrExp();
    Value parseAndExp();
    Value parseEqExp();
    Value parseRelExp();
    Value parseAddExp();
    Value parseMulExp();
    Value parseUnaryExp();
    Value parsePrimaryExp();
    
public:
    Parser(const string& expression);
    string evaluate();
};

#endif
