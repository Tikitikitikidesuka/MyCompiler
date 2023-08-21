#include "../include/parser.h"

std::unique_ptr<Token> Parser::getNewToken() {
    return std::move(this->lexer.getToken());
}

std::unique_ptr<Expression> Parser::logError(char* msg) {
    fprintf(stderr, msg);
    return nullptr;
}

std::unique_ptr<Expression> Parser::primaryExpression() {
    // CLASIFIES SIMPLE EXPRESIONS
    switch (this->current_token->getType()) {
        case TOK_NUM:
        {// conversión Token a numToken (a un puntero)
            std::unique_ptr<NumToken> num_token(dynamic_cast<NumToken*>(current_token.get()));
            ParseNumExpr(std::make_unique<ExpressionNum>(ExpressionNum(num_token->getNum())));
        }
        case TOK_ID:
        {
            std::unique_ptr<IdToken> id_token(dynamic_cast<IdToken*>(current_token.get()));
            ParseIdExpr(std::make_unique<ExpressionId>(ExpressionId(id_token->getId())));
            
        }
        case TOK_RW:
        {
            std::unique_ptr<RWToken> rw_token(dynamic_cast<RWToken*>(current_token.get()));
            switch (rw_token->getType()) {
                case TOK_PARENTHESIS_OPEN:
                    ParseParenExpr()
            }
            return
            
        }
            return;
    }
}