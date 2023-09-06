#include "codegen.h"

llvm::Value* logError(const std::string& msg) {
    std::cerr << msg;
    return nullptr;
}

void* CodeGenerator::visit(VariableExpression* expr) {
    if (this->named_values.count(expr->getName())) { // If var exists
        llvm::AllocaInst* var = this->named_values[expr->getName()];
        return this->builder.CreateLoad(var->getAllocatedType(), var, expr->getName());
    }

    return this->logError("Unkown variable (" + expr->getName() + ")");
}

void* CodeGenerator::visit(VariableDeclarationExpression* expr) {
    if (this->named_values.count(expr->getName())) { // If var does not exist
        this->named_values.insert({expr->getName(), this->builder.CreateAlloca(
                llvm::IntegerType::get(*this->context, 32),
                nullptr, expr->getName())});

        llvm::AllocaInst* var = this->named_values[expr->getName()];
        return this->builder.CreateLoad(var->getAllocatedType(), var, expr->getName());
    }

    return this->logError("Variables can not be redeclared(" + expr->getName() + ")");
}

void* CodeGenerator::visit(NumberExpression* expr) {
     return llvm::ConstantInt::get(
            llvm::IntegerType::get(*this->context, 32),
            expr->getValue(), true);
}

void* CodeGenerator::visit(BinaryExpression* expr) {
    if (expr->getOperation() == OP_ASSIGNMENT) {
        VariableDeclarationExpression* lhs = static_cast<VariableDeclarationExpression*>(expr->getLhs());
        if (!lhs)
            return this->logError("Left hand side operator of an assignment must be a variable declaration");

        llvm::Value* value = static_cast<llvm::Value*>(expr->getRhs()->accept(*this));
        if (!value)
            return nullptr;

        llvm::Value* var = this->named_values[lhs->getName()];
        if (!var)
            return this->logError("Unkown variable name (" + lhs->getName() + ")");
    }
}
