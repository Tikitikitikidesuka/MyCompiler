#include "lexer.h"
int32_t NumToken::getNum() {
    return this->num;
}

std::string IdToken::getId() {
    return this->id;
}

std::unique_ptr<Token> Lexer::getToken() {
    std::string input_buffer;

    char input_char = this->stream.get();

    // Consume separators or EOF
    while (input_char != EOF && input_char <= ' ')
        input_char = this->stream.get();

    // Return if token is EOF
    if (input_char == EOF)
        return std::make_unique<Token>(RWToken(RWTokenType::TOK_EOF));

    // Token is number literal
    if (isdigit(input_char)) {
        input_buffer += input_char;
        input_char = this->stream.peek(); // Read char without consuming

        while (isdigit(input_char)) {
            this->stream.get(); // Consume peeked char
            input_buffer += input_char;
            input_char = this->stream.peek();
        }
    } else { // Token is identifier or reserved word
        while (input_char > ' ') {
            input_buffer += input_char;

            // Check if token is a reserved word
            RWTokenType rw_type = resolveReservedWord(input_buffer);
            if (rw_type != RWTokenType::TOK_UNKOWN)
                return std::make_unique<Token>(RWToken(rw_type));

            // Check if token is an identifier
            if (isalnum(input_char) && !isalnum(this->stream.peek()))
                return std::make_unique<Token>(IdToken(input_buffer));

            input_char = this->stream.get();
        }
    }

    return nullptr;
}
