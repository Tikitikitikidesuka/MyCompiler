#ifndef AST_H
#define AST_H


#include <string>
#include <memory>

#include "lexer.h"

// MISCELLANEOUS
enum Operator {
    ADDITION,
    SUBTRACTION
};


class Expression {
public:
    virtual ~Expression() = default;
};

// SIMPLE EXPRESSIONS

class ExpressionId : public Expression {
private:
    std::string name;
public:
    ExpressionId(std::string name) 
    : name(name) {}
};

class ExpressionNum : public Expression {
private:
    int32_t value;
public:
    ExpressionNum(int32_t value)
    : value(value) {}
};

// BINARY EXPRESSIONS

class BinaryExpression : public Expression {
private:
    std::unique_ptr<Expression> lhs, rhs;
    Operator operation;
public:
    BinaryExpression(Operator operation, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) 
    : operation(operation), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

// PARENTHESIS EXPRESSIONS

class ParenthesisExpr : public Expression {
private:
    std::unique_ptr<Expression> inner_expression;
public:
    ParenthesisExpr(std::unique_ptr<Expression> expr)
    : inner_expression(std::move(expr)) {}
};


#endif