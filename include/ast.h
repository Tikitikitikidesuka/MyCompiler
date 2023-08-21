#ifndef AST_H
#define AST_H


#include <string>
#include <memory>
#include <sstream>

#include "lexer.h"

// MISCELLANEOUS
enum Operator {
    OP_ADDITION,
    OP_SUBTRACTION,
    OP_ASSIGNMENT,
};

enum ExprType {
    EXPR_NUM,
    EXPR_ID,
    EXPR_PARENTHESIS,
    EXPR_BINARY
};

class Expression {
public:
    virtual ~Expression() = default;
    virtual ExprType getType() = 0;
    virtual std::string toString() = 0;
};

// SIMPLE EXPRESSIONS

class IdExpression : public Expression {
private:
    std::string name;
public:
    IdExpression(std::string name)
    : name(name) {}
    ExprType getType() { return EXPR_ID; }

    std::string toString() {
        return "ID: " + this->name;
    }
};

class NumberExpression : public Expression {
private:
    int32_t value;
public:
    NumberExpression(int32_t value)
    : value(value) {}
    ExprType getType() { return EXPR_NUM; }

    std::string toString() {
        return "NUM: " + std::to_string(this->value);
    }
};

// BINARY EXPRESSIONS

class BinaryExpression : public Expression {
private:
    std::unique_ptr<Expression> lhs, rhs;
    Operator operation;
public:
    BinaryExpression(Operator operation, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) 
    : operation(operation), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    ExprType getType() { return EXPR_BINARY; }

    std::string toString() {
        return "BIN: " + std::to_string(this->operation) + "\n\t" + this->lhs->toString() + "\n\t" + this->rhs->toString();
    }
};

// PARENTHESIS EXPRESSIONS

class ParenthesisExpression : public Expression {
private:
    std::unique_ptr<Expression> inner_expression;
public:
    ParenthesisExpression(std::unique_ptr<Expression> expr)
    : inner_expression(std::move(expr)) {}
    ExprType getType() { return EXPR_PARENTHESIS; }

    std::string toString() {
        return "PARENTHESIS:\n\t" + this->inner_expression->toString();
    }
};


#endif