#include <iostream>

#include "lexer.h"

int main() {
    Lexer lexer;
    TokenResult token(tok_unknown, "");
    std::string input;
    while (token.token != tok_eof) {
        token = lexer.getToken();
        switch (token.token)
        {
        case tok_fn:
            std::cout << "FUNCION -> " << token.text << "\n";
            break;
        case tok_identifier:
            std::cout << "INDENTIFIER -> " << token.text << "\n";
            break;
        case tok_number:
            std::cout << "NUMBER -> " << token.text << "\n";
            break;
        
        case tok_while:
            std::cout << "WHILE -> " << token.text << "\n";
            break;
        
        case tok_unknown:
            std::cout << "UNKNOWN ->  " << token.text << "\n";
            break;

        //separators
        case tok_scolon:
            std::cout << "SEMICOLON -> " << token.text << "\n";
            break;
        
        case tok_colon:
            std::cout << "COLON -> " << token.text << "\n";
            break;
        
        //parenthesis
        case tok_oparenthesis:
            std::cout << "PARENTHESIS OP -> " << token.text << "\n";
            break;
        case tok_cparenthesis:
            std::cout << "PARENTHESIS CL -> " << token.text << "\n";
            break;
        case tok_osquerebr:
            std::cout << "SQUERE BRACKET OP -> " << token.text << "\n";
            break;
        case tok_csquerebr:
            std::cout << "SQUERE BRACKET CL -> " << token.text << "\n";
            break;
        case tok_okey:
            std::cout << "KEY BRACKET OP -> " << token.text << "\n";
            break;
        case tok_ckey:
            std::cout << "KEY BRACKET CL -> " << token.text << "\n";
            break;
        
        default:
            std::cout << "OTHER: " << token.text << "\n";
            break;
        }
    }
    return 0;
}
