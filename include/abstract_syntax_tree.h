#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <string>
#include <memory>
#include <vector>

enum Operation {
    addition,
    subtraction,
    product,
    division
};

class ExprAST {
public:
    virtual ~ExprAST() = default;
}; 

class NumberExprAST : public ExprAST {
private:
    int value;

public: 
    NumberExprAST(int value)
    : value(value) {};
};

class VariableExprAST : public ExprAST {    
private:
    std::string name;
    //TODO: type
public:
    VariableExprAST(const std::string& name)
    : name(name) {};
};

class BinaryExprAST : public ExprAST {
private:
    std::unique_ptr<ExprAST> operator1, operator2;
    Operation operation;

public: 
    BinaryExprAST(std::unique_ptr<ExprAST> operator1, std::unique_ptr<ExprAST> operator2, Operation operation) 
    : operator1(std::move(operator1)), operator2(std::move(operator2)), operation(operation) {}
};

class CallExprAST : public ExprAST { 
private:
    std::string fn_name;
    std::vector<std::unique_ptr<ExprAST>> arguments;

public:
    CallExprAST(const std::string& name, std::vector<std::unique_ptr<ExprAST>> arguments)
    : fn_name(name), arguments(std::move(arguments)) {}
};

class PrototypeAST {
private:
    std::string name;
    std::vector<std::string> args;

public:
    PrototypeAST(const std::string& name, std::vector<std::string> args)
    : name(name), args(std::move(args)) {}
}; 

class FunctionAST {
private:
    std::unique_ptr<PrototypeAST> fn_proto;
    std::unique_ptr<ExprAST> body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> fn_proto, std::unique_ptr<ExprAST> body)
    : fn_proto(std::move(fn_proto)), body(std::move(body)) {}
};

#endif //ABSTRACT_SYNTAX_TREE_H
