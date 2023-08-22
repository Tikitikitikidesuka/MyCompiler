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
    std::unique_ptr<Expression> subParseExpr(); // clasifies the current token and consumes it
    std::unique_ptr<Expression> parsePrimaryExpr();
    std::unique_ptr<Expression> parseNumExpr();
    std::unique_ptr<Expression> parseIdExpr();
    std::unique_ptr<Expression> parseParenthesisExpr();
    std::unique_ptr<Expression> parseBinaryRhsExpr(std::unique_ptr<Expression> lhs);

public:
    Parser() : current_token(Token(TOK_INVALID, "")) {}
    std::unique_ptr<Expression> parseExpr(); // clasifies the current token and consumes it
};


#endif