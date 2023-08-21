#include "lexer.h"
int32_t NumToken::getNum() {
    return this->num;
}

std::string IdToken::getId() {
    return this->id;
}

Token Lexer::nextToken() const {
    std::string input_buffer;

    char input_char = this->stream.get();

    // Consume separators or EOF
    while (input_char != EOF && input_char <= ' ')
        input_char = this->stream.get();

    // Return if token is EOF
    if (input_char == EOF)
        return Token(TokenType::TOK_EOF, input_buffer);

    // Token is number literal
    if (isdigit(input_char)) {
        input_buffer += input_char;
        input_char = this->stream.peek(); // Read char without consuming

        while (isdigit(input_char)) {
            this->stream.get(); // Consume peeked char
            input_buffer += input_char;
            input_char = this->stream.peek();
        }

        return Token(TokenType::TOK_NUM, input_buffer);
    } else { // Token is identifier or reserved word
        while (input_char > ' ') {
            input_buffer += input_char;

            // Check if token is a reserved word
            TokenType rw_type = resolveReservedWord(input_buffer);
            if (rw_type != TokenType::TOK_INVALID)
                return Token(rw_type, input_buffer);

            // Check if token is an identifier
            if (isalnum(input_char) && !isalnum(this->stream.peek()))
                return Token(TokenType::TOK_ID, input_buffer);

            input_char = this->stream.get();
        }
    }

    return Token(TokenType::TOK_INVALID, input_buffer);
}
