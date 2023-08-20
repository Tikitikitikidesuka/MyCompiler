#ifndef LEXER_H
#define LEXER_H


#include <iostream>

enum TokenType {
    TOK_NUM,
    TOK_ID,
    TOK_RW,
};

enum RWTokenType {
    TOK_EOF,

    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MINUS,
    TOK_PARENTHESIS_OPEN,
    TOK_PARENTHESIS_CLOSE,

    TOK_UNKOWN,
};

inline RWTokenType resolveReservedWord(const std::string& str) {
    if (str == "+") return TOK_PLUS;
    if (str == "-") return TOK_MINUS;
    if (str == "=") return TOK_ASSIGN;
    if (str == "(") return TOK_PARENTHESIS_OPEN;
    if (str == ")") return TOK_PARENTHESIS_CLOSE;
    return TOK_UNKOWN;
}

class Token {
private:
    TokenType type;
public:
    virtual ~Token() = default;
    Token(TokenType type) : type(type) {}
    TokenType getType() { return this->type; }
};

class NumToken : public Token {
private:
    int32_t num;
public:
    NumToken(int32_t num) : Token(TokenType::TOK_NUM), num(num) {}
};

class IdToken : public Token {
private:
    std::string id;
public:
    IdToken(const std::string& id) : Token(TokenType::TOK_ID), id(id) {}
};

class RWToken : public Token {
private:
    RWTokenType rw_type;
public:
    RWToken(RWTokenType rw_type) : Token(TokenType::TOK_RW), rw_type(rw_type) {}
};


class Lexer {
private:
    std::istream& stream;
public:
    Lexer() : stream(std::cin) {};
    Lexer(std::istream& stream) : stream(stream) {};
    std::unique_ptr<Token> getToken();
};


#endif //LEXER_H
