#ifndef PARSER_H
#define PARSER_H

#include <memory>

#include "lexer.h"
#include "abstract_syntax_tree.h"

class Parser {
private:
    Lexer lexer;
    TokenResult curr_token;

public:
    TokenResult getNextToken();
    std::unique_ptr<ExprAST> logError(const std::string& error);
    std::unique_ptr<PrototypeAST> logErrorP(const std::string& error);
    std::unique_ptr<ExprAST> parseNumberExpr();
    std::unique_ptr<ExprAST> parseParenthesisExpr();
    std::unique_ptr<ExprAST> parseIdentifierExpr();
};


#endif //PARSER_H
