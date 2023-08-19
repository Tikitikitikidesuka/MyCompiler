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
        this->str_to_token[":"] = Token::tok_colon;
        this->str_to_token[";"] = Token::tok_scolon;
        this->str_to_token["("] = Token::tok_oparenthesis;
        this->str_to_token[")"] = Token::tok_cparenthesis;
        this->str_to_token["{"] = Token::tok_okey;
        this->str_to_token["}"] = Token::tok_ckey;
        this->str_to_token["["] = Token::tok_osquerebr;
        this->str_to_token["]"] = Token::tok_csquerebr;
        this->str_to_token["+"] = Token::tok_plus;
        this->str_to_token["-"] = Token::tok_minus;
        this->str_to_token["*"] = Token::tok_multiply;
        this->str_to_token["/"] = Token::tok_divide;
        this->str_to_token[","] = Token::tok_comma;
        this->str_to_token["fn"] = Token::tok_fn;
        this->str_to_token["while"] = Token::tok_while;
    }
    TokenResult getToken();
};


#endif //LEXER_H
