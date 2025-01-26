#include "Token.h"
#include <cctype>
using namespace std;

Token::Token(TokenType type, string value) : type(type), value(value) {}

Tokenizer::Tokenizer(const string& expression) : input(expression), pos(0) {}

Token Tokenizer::getNextToken() {
    while (pos < input.size() && isspace(input[pos])) pos++;

    if (pos >= input.size()) return Token(TokenType::END, "");

    if (isdigit(input[pos]) || input[pos] == '-') {
        string num;
        while (pos < input.size() && (isdigit(input[pos]) || input[pos] == '-'))
            num += input[pos++];
        return Token(TokenType::INTEGER, num);
    }

    if (input.compare(pos, 4, "true") == 0) {
        pos += 4;
        return Token(TokenType::BOOLEAN, "true");
    }

    if (input.compare(pos, 5, "false") == 0) {
        pos += 5;
        return Token(TokenType::BOOLEAN, "false");
    }

    // Operadores compostos
    string op2 = input.substr(pos, 2);
    if (op2 == "==" || op2 == "!=" || op2 == "<=" || op2 == ">=" || op2 == "&&" || op2 == "||") {
        pos += 2;
        return Token(TokenType::OPERATOR, op2);
    }

    // Operadores simples
    string operators = "+-*/()<>";
    if (operators.find(input[pos]) != string::npos) {
        return Token(TokenType::OPERATOR, string(1, input[pos++]));
    }

    return Token(TokenType::END, "");
}
