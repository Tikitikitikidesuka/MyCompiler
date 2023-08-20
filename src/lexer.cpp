#include "lexer.h"

#include <iostream>
#include <vector>

std::unique_ptr<Token> Lexer::getToken() {
    std::string input_buffer;

    char input_char = getchar();

    // Consume separators or EOF
    while (input_char != EOF && input_char <= ' ')
        input_char = getchar();

    // Return if token is EOF
    if (input_char == EOF)
        return std::make_unique<Token>(RWToken(RWTokenType::TOK_EOF));

    // Token is number literal
    if (isdigit(input_char)) {
        input_buffer += input_char;
        input_char = std::cin.peek(); // Read char without consuming

        while (isdigit(input_char)) {
            getchar(); // Consume peeked char
            input_buffer += input_char;
            input_char = std::cin.peek();
        }
    } else { // Token is identifier or reserved word
        while (input_char > ' ') {
            input_buffer += input_char;

            // Check if token is a reserved word
            RWTokenType rw_type = resolveReservedWord(input_buffer);
            if (rw_type != RWTokenType::TOK_UNKOWN)
                return std::make_unique<Token>(RWToken(rw_type));

            // Check if token is an identifier
            if (isalnum(input_char) && !isalnum(std::cin.peek()))
                return std::make_unique<Token>(IdToken(input_buffer));

            input_char = getchar();
        }
    }

    return std::make_unique<Token>(RWToken(RWTokenType::TOK_UNKOWN));
}
