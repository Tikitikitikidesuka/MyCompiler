#include <iostream>
#include "src/Lexer.h"

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
            std::cout << "FUNCION: " << token.text << "\n";
            break;
        case tok_identifier:
            std::cout << "INDENTIFIER: " << token.text << "\n";
            break;
        case tok_number:
            std::cout << "NUMBER: " << token.text << "\n";
            break;
        
        case tok_while:
            std::cout << "WHILE: " << token.text << "\n";
            break;
        
        case tok_unknown:
            std::cout << "UNKNOWN: " << token.text << "\n";
            break;
        
        default:
            break;
        }
    }
    return 0;
}
