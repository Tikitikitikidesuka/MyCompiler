#ifndef MYCOMPILER_LEXER_H
#define MYCOMPILER_LEXER_H

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


#endif //MYCOMPILER_LEXER_H
