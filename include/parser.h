#ifndef PARSER_H
#define PARSER_H


#include <iostream>
#include <string>
#include <memory>

#include "lexer.h"
#include "ast.h"


class Parser {
private:
    Lexer lexer;
    Token current_token;

    Token getNewToken();
    std::unique_ptr<Expression> logError (const std::string& msg);
    std::unique_ptr<Expression> parseLiteralExpr();
    std::unique_ptr<Expression> parseNumExpr();
    std::unique_ptr<Expression> parseIdExpr();
    std::unique_ptr<Expression> parseParenthesisExpr();
    std::unique_ptr<Expression> parseBinaryExpr();
    std::unique_ptr<Expression> parseOperationExpr(std::unique_ptr<Expression> lhs);
    std::unique_ptr<Expression> parseAssignmentExpr(std::unique_ptr<Expression> lhs);

public:
    Parser() : current_token(Token(TOK_INVALID, "")) {}
    std::unique_ptr<Expression> parseExpr(); // clasifies the current token and consumes it
};


#endif