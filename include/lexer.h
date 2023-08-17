#ifndef LEXER_H
#define LEXER_H

enum Token {
    tok_eof,

    // Keywords
    tok_fn,
    tok_while,

    // Other
    tok_identifier,
    tok_number,

    tok_unknown,
};

class Lexer {
public:
    Token getToken();
};


#endif //LEXER_H
