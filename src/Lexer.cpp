#include "Lexer.h"

#include <regex>
#include <iostream>

Token Lexer::getToken() {
    std::string input;
    if (!(std::cin >> input)) return Token::tok_eof;

    if (std::regex_match(input, std::regex("fn"))) return Token::tok_fn;
    if (std::regex_match(input, std::regex("while"))) return Token::tok_while;
    if (std::regex_match(input, std::regex("[a-zA-Z][a-zA-Z0-9]*"))) return Token::tok_identifier;
    if (std::regex_match(input, std::regex("[0-9]+"))) return Token::tok_number;

    return Token::tok_unknown;
}
