#ifndef LEXER_H
#define LEXER_H


#include <iostream>
#include <unordered_map>

enum TokenType {
    TOK_EOF,

    TOK_ID,
    TOK_NUM,

    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MINUS,
    TOK_PARENTHESIS_OPEN,
    TOK_PARENTHESIS_CLOSE,
};

class Token {
private:
    TokenType type;
public:
    virtual ~Token() = default;
    TokenType getType() {
        return this->type;
    }
};

class NumToken : public Token {
private:
    int32_t num;
public:
    NumToken(int32_t num) : type(Token::TOK_NUM), num(num) {}
};

class IdToken : public Token {
private:
    std::string id;
public:
    IdToken(const std::string& id) : type(Token::TOK_ID), id(id) {}
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
