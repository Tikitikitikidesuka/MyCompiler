#include "lexer.h"

#include <regex>
#include <iostream>
#include <vector>

TokenResult Lexer::getToken() {
    std::unordered_map<std::string, Token> str_to_token;
    str_to_token[":"] = Token::tok_colon;
    str_to_token[";"] = Token::tok_scolon;
    str_to_token["("] = Token::tok_oparenthesis;
    str_to_token[")"] = Token::tok_cparenthesis;
    str_to_token["{"] = Token::tok_okey;
    str_to_token["}"] = Token::tok_ckey;
    str_to_token["["] = Token::tok_osquerebr;
    str_to_token["]"] = Token::tok_csquerebr;
    str_to_token["fn"] = Token::tok_fn;
    str_to_token["while"] = Token::tok_while;

    std::string input_buffer;

    char input_char = getchar();
    while (input_char <= ' ') input_char = getchar();

    if (isnumber(input_char)) {
        do {
            input_buffer += input_char;
            input_char = std::cin.peek();
            if (isnumber(input_char)) getchar();
        } while (isnumber(input_char));

        return TokenResult(Token::tok_number, input_buffer);
    } else {
        while (input_char > ' ') {
            input_buffer += input_char;

            for (const auto &token_test: str_to_token) {
                if (input_buffer == token_test.first)
                    return TokenResult(token_test.second, input_buffer);
            }

            if (!isalnum(std::cin.peek()))
                return TokenResult(Token::tok_identifier, input_buffer);

            input_char = getchar();
        }
    }

    return TokenResult(Token::tok_unknown, input_buffer);
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
