#include "codegen.h"

llvm::Value* logError(const std::string& msg) {
    std::cerr << msg;
    return nullptr;
}

void CodeGenerator::visit(VariableExpression* expr) {
    if (this->named_values.count(expr->getName())) // If var exists
        this->named_values[expr->getName()]; // Check what to do with
    nullptr;
}

void CodeGenerator::visit(VariableDeclarationExpression* expr) {
}

void CodeGenerator::visit(NumberExpression* expr) {
    // Check what to do with
     llvm::ConstantInt::get(
            llvm::IntegerType::get(*this->context, 8 * sizeof(expr->getValue())),
            expr->getValue(), true);
}

void CodeGenerator::visit(BinaryExpression* expr) {

}
