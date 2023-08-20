#include "lexer.h"

#include <regex>
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
            for (const auto& token_test : this->str_to_token) {
                if (input_buffer == token_test.first)
                    return std::make_unique<Token>(RWToken(token_test.second));
            }

            // Check if token is an identifier
            if (isalnum(input_char) && !isalnum(std::cin.peek()))
                return std::make_unique<Token>(IdToken(input_buffer));

            input_char = getchar();
        }
    }

    return std::make_unique<Token>(Token(TokenType::TOK_UNKOWN));
}

/*
TokenResult Lexer::getToken() {
    std::string input_str = "";
    char input = state;
    switch (input)
    {
    //separators
    case ':':
        state = '\r';
        return TokenResult(Token::tok_colon, ":");
    case ';':
        state = '\r';
        return TokenResult(Token::tok_scolon, ";");
    case '(':
        state = '\r';
        return TokenResult(Token::tok_oparenthesis, "(");
    case ')':
        state = '\r';
        return TokenResult(Token::tok_cparenthesis, ")");
    case '{':
        state = '\r';
        return TokenResult(Token::tok_okey, "{");
    case '}':
        state = '\r';
        return TokenResult(Token::tok_ckey, "}");
    case '[':
        state = '\r';
        return TokenResult(Token::tok_osquerebr, "[");
     case ']':
        state = '\r';
        return TokenResult(Token::tok_csquerebr, "]");
    default:
        break;
    }
    
    if (!(std::cin >> input)) return TokenResult(Token::tok_eof, input_str);
    while (isalnum(input)) {
        input_str += input;
        std::cin >> input;
    } 
    this->state = input;

    if (std::regex_match(input_str, std::regex("fn"))) return TokenResult(Token::tok_fn, input_str);
    if (std::regex_match(input_str, std::regex("while"))) return TokenResult(Token::tok_while, input_str);
    if (std::regex_match(input_str, std::regex("[a-zA-Z][a-zA-Z0-9]*"))) return TokenResult(Token::tok_identifier, input_str);
    if (std::regex_match(input_str, std::regex("[0-9]+"))) return TokenResult(Token::tok_number, input_str);

    return TokenResult(Token::tok_unknown, input_str);
}
*/
