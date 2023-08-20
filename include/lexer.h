#ifndef LEXER_H
#define LEXER_H


#include <iostream>
#include <unordered_map>

enum Token {
    TOK_EOF,

    TOK_ID,
    TOK_NUM,

    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MINUS,
    TOK_PARENTHESIS_OPEN,
    TOK_PARENTHESIS_CLOSE,
};

class TokenResult {
public:
    Token token;
    std::string text;

    TokenResult(Token token, std::string text)
    : token(token), text(text) {};
};

class Lexer {
private:
    char state;
    std::unordered_map<std::string, Token> str_to_token;
public:
    Lexer() {
        this->str_to_token["+"] = Token::TOK_PLUS;
        this->str_to_token["-"] = Token::TOK_MINUS;
        this->str_to_token["="] = Token::TOK_ASSIGN;
        this->str_to_token["("] = Token::TOK_PARENTHESIS_OPEN;
        this->str_to_token[")"] = Token::TOK_PARENTHESIS_CLOSE;
    }
    TokenResult getToken();
};


#endif //LEXER_H
