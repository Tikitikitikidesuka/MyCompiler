#include "parser.h"

TokenResult Parser::getNextToken() {
    this->curr_token = this->lexer.getToken();
    return this->curr_token;
}

std::unique_ptr<ExprAST> logError(const std::string& error) {
    std::cerr << "Error: " << error << "\n";
    return nullptr;
}

std::unique_ptr<PrototypeAST> logErrorP(const std::string& error) {
    this->logError(error);
    return nullptr;
}

std::unique_ptr<ExprAST> Parser::parseNumberExpr() {
    auto result = std::make_unique<NumberExprAST>(
            stoi(this->curr_token.text));
    this->getNextToken();
    return std::move(result);
}

std::unique_ptr<ExprAST> Parser::parseParenthesisExpr() {
    this->getNextToken();
    auto ast = this->parseExpresion();

    if (!ast)
        return nullptr;

    if (this->curr_token.token != Token::tok_cparenthesis)
        return this->logError("Expected ')'");

    this->getNextToken();
    return ast;
}

std::unique_ptr<ExprAST> Parser::parseIdentifierExpr() {
    std::string name = this->curr_token.text;

    this->getNextToken();

    if (this->curr_token.token != Token::tok_cparenthesis)
        return std::make_unique<VariableExprAST>(name);

    this->getNextToken();

    std::vector<std::unique_ptr<ExprAST>> args;
    if (this->curr_token.token != Token::tok_cparenthesis) {
        while (true) {
            auto arg = this->parseExpression();

            if (arg) args.push_back(std::move(arg));
            else return nullptr;

            if (this->curr_token.token == Token::tok_cparenthesis) break;

            if (this->curr_token.token != Token::tok_comma)
                return this->logError("Expected ')' or ',' in argument list");

            this->getNextToken();
        }
    }

    this->getNextToken();

    return std::make_unique<CallExprAST>(name, std::move(args));
}
