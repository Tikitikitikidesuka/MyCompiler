#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <string>
#include <memory>

#include "lexer.h"
#include "ast.h"


class Parser {
private:
    std::unique_ptr<Token> current_token;
    Lexer lexer;

public:
    std::unique_ptr<Token> getNewToken();
    std::unique_ptr<Expression> logError (char* msg);
    std::unique_ptr<Expression> primaryExpression(); // clasifies the current token and consumes it

};


#endif