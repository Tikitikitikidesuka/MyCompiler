#ifndef LEXER_H
#define LEXER_H


#include <iostream>
#include <unordered_map>

enum Token {
    tok_eof,

    // Keywords
    tok_fn,
    tok_while,

    //separators
    tok_scolon,
    tok_colon,
    tok_comma,

    // operators
    tok_plus,
    tok_minus,
    tok_multiply,
    tok_divide,

    //parenthesis
    tok_oparenthesis, 
    tok_cparenthesis,
    tok_osquerebr,
    tok_csquerebr,
    tok_okey,
    tok_ckey,

    // Other
    tok_identifier,
    tok_number,

    tok_unknown,
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
        this->str_to_token["+"] = Token::TOKE_PLUS;
        this->str_to_token["-"] = Token::TOK_MINUS;
        this->str_to_token["="] = Token::TOK_ASSIGN;
        this->std_to_token["("] = Token::TOK_PARENTHESIS_OPEN;
        this->std_to_token[")"] = Token::TOK_PARENTHESIS_CLOSE;
    }
    TokenResult getToken();
};


#endif //LEXER_H
