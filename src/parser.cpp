#include "parser.h"

Token Parser::getNewToken() {
    this->current_token = this->lexer.nextToken();
    return this->current_token;
}

std::unique_ptr<Expression> Parser::logError(const std::string& msg) {
    std::cerr << msg;
    return nullptr;
}

std::unique_ptr<Expression> Parser::parseExpr() {
    if (this->current_token.getType() == TOK_PARENTHESIS_OPEN) {
        return this->parseParenthesisExpr();

    } else {
        return this->parseBinaryExpr();
    }
}

std::unique_ptr<Expression> Parser::parseParenthesisExpr() {
    std::unique_ptr<Expression> expr = this->parseExpr();

    if (expr && this->getNewToken().getType() == TOK_PARENTHESIS_CLOSE) {
        return std::make_unique<ParenthesisExpression>(ParenthesisExpression(std::move(expr)));
    } else {
        return nullptr;
    }
}
std::unique_ptr<Expression> Parser::parseLiteralExpr() {
    switch (this->current_token.getType()) {
        case TOK_NUM:
            return this->parseNumExpr();
        case TOK_ID:
            return this->parseIdExpr();
        default:
            return this->logError("Unexpected Token: " + this->current_token.getLexeme());
    }
}

std::unique_ptr<Expression> Parser::parseNumExpr() {
    this->getNewToken();
    return std::make_unique<NumberExpression>(NumberExpression(stoi(this->current_token.getLexeme())));
}

std::unique_ptr<Expression> Parser::parseIdExpr() {
    this->getNewToken();
    return std::make_unique<IdExpression>(IdExpression(this->current_token.getLexeme()));
}

std::unique_ptr<Expression> Parser::parseBinaryExpr() {
    auto expr = this->parseLiteralExpr();
    if (expr == nullptr) return expr;

    this->getNewToken();
    if (this->current_token.getType() == TOK_PLUS || this->current_token.getType() == TOK_MINUS) {
        return this->parseOperationExpr(std::move(expr));
    }
    
    if (this->current_token.getType() == TOK_ASSIGN) {
        return this->parseAssignmentExpr(std::move(expr));
    }

    return std::move(expr);
}

std::unique_ptr<Expression> Parser::parseOperationExpr(std::unique_ptr<Expression> lhs) {
    TokenType operation = this->current_token.getType();
    
}

std::unique_ptr<Expression> Parser::parseAssignmentExpr(std::unique_ptr<Expression> lhs) {
    return nullptr;
}