#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

enum class TokenType {
    INTEGER, BOOLEAN, OPERATOR, END
};

class Token {
public:
    TokenType type;
    string value;

    Token() : type(TokenType::END), value("") {}
    Token(TokenType type, string value);
};

class Tokenizer {
private:
    string input;
    size_t pos;

public:
    Tokenizer(const string& expression);
    Token getNextToken();
};

#endif
