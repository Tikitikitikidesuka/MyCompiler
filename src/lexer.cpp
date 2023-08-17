#include "lexer.h"

#include <regex>
#include <iostream>
#include <vector>

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
