#ifndef LEXER_H
#define LEXER_H


#include <iostream>
#include <memory>

enum TokenType {
    TOK_EOF,

    TOK_ASSIGN,
    TOK_PLUS,
    TOK_MINUS,
    TOK_PARENTHESIS_OPEN,
    TOK_PARENTHESIS_CLOSE,

    TOK_ID,
    TOK_NUM,

    TOK_INVALID,
};

inline TokenType resolveReservedWord(const std::string& str) {
    if (str == "+") return TOK_PLUS;
    if (str == "-") return TOK_MINUS;
    if (str == "=") return TOK_ASSIGN;
    if (str == "(") return TOK_PARENTHESIS_OPEN;
    if (str == ")") return TOK_PARENTHESIS_CLOSE;
    return TOK_INVALID;
}

class Token {
private:
    TokenType type;
    std::string lexeme;
public:
    Token(TokenType type, const std::string& lexeme) : type(type), lexeme(lexeme) {}
    TokenType getType() const { return this->type; }
    std::string getLexeme() const { return this->lexeme; }
    friend bool operator==(const Token& lhs, const Token& rhs);
};

inline bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.type == rhs.type
           && (lhs.type != TokenType::TOK_NUM || lhs.lexeme == rhs.lexeme)
           && (lhs.type != TokenType::TOK_ID || lhs.lexeme == rhs.lexeme);
}

class Lexer {
private:
    std::istream& stream;
public:
    Lexer() : stream(std::cin) {};
    Lexer(std::istream& stream) : stream(stream) {};
    Token nextToken() const;
};


#endif //LEXER_H
