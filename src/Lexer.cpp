#include "Lexer.h"

#include <regex>
#include <iostream>
#include <vector>

TokenResult Lexer::getToken() {
    std::string input_str = "";
    char input = state;
    
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
