#ifndef LEXER_H
#define LEXER_H


#include <iostream>

enum Token {
    tok_eof,

    // Keywords
    tok_fn,
    tok_while,

    //separators
    tok_scolon,
    tok_colon,

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
public:
    TokenResult getToken();
};


#endif //LEXER_H
