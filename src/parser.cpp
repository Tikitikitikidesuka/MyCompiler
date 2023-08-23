#include "parser.h"

Token Parser::getNewToken() {
    this->current_token = this->lexer.nextToken();
    return this->current_token;
}

std::unique_ptr<Expression> Parser::logError(const std::string& msg) {
    std::cerr << msg;
    return nullptr;
}

std::unique_ptr<Expression> Parser::parseStatement() {
    this->getNewToken();
    
    if (this->current_token.getType() == TOK_EOF)
        return nullptr;

    return this->parseExpr();
}

std::unique_ptr<Expression> Parser::parseExpr() {
    std::unique_ptr<Expression> lhs = this->parsePrimaryExpr();

    if (!lhs)
        return nullptr;

    return this->parseBinaryRhsExpr(0, std::move(lhs));
}

std::unique_ptr<Expression> Parser::parseParenthesisExpr() {
    this->getNewToken(); // Consume '('

    std::unique_ptr<Expression> expr = this->parseExpr();
    if (!expr) {

        return nullptr;
    }

    if (this->current_token.getType() != TOK_PARENTHESIS_CLOSE)
        return this->logError("Expected )");

    this->getNewToken(); // Consume ')'

    return expr;
}

std::unique_ptr<Expression> Parser::parsePrimaryExpr() {
    switch (this->current_token.getType()) {
        case TOK_NUM:
            return this->parseNumExpr();
        case TOK_ID:
            return this->parseIdExpr();
        case TOK_PARENTHESIS_OPEN:
            return this->parseParenthesisExpr();
        case TOK_EOF:
            return this->logError("Unexpected end of file");
        default:
            return this->logError("Unexpected Token: " + this->current_token.getLexeme());
    }
}

std::unique_ptr<Expression> Parser::parseNumExpr() {
    std::unique_ptr<Expression> expr = std::make_unique<NumberExpression>(
            NumberExpression(stoi(this->current_token.getLexeme())));

    this->getNewToken();

    return std::move(expr);
}

std::unique_ptr<Expression> Parser::parseIdExpr() {
    std::unique_ptr<Expression> expr = std::make_unique<IdExpression>(
            IdExpression(this->current_token.getLexeme()));

    this->getNewToken();

    return std::move(expr);
}

std::unique_ptr<Expression> Parser::parseBinaryRhsExpr(int prev_expr_priority,std::unique_ptr<Expression> lhs) {
    while (true) {
        if (this->current_token.getType() == TOK_SEPARATOR
        || this->current_token.getType() == TOK_PARENTHESIS_CLOSE)
            return std::move(lhs);

        Operation operation = resolveOperation(this->current_token.getType());

        if (operation == OP_INVALID)
            return this->logError("Invalid operator");

        int curr_priority = operationPriority(operation);
        if (curr_priority < prev_expr_priority)
            return lhs;

        this->getNewToken(); // Consume operator

        std::unique_ptr<Expression> rhs = this->parsePrimaryExpr();
        if (!rhs)
            return nullptr;

        Operation next_operation = resolveOperation(this->current_token.getType());
        int next_priority = operationPriority(next_operation);
        if (next_priority > curr_priority) {
            rhs = parseBinaryRhsExpr(curr_priority + 1, std::move(rhs));
            if (!rhs) 
                return nullptr;
        }

        lhs = std::make_unique<BinaryExpression>(operation, std::move(lhs), std::move(rhs));
    }
}