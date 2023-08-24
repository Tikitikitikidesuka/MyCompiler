#include "ast.h"

llvm::Value* NumberExpression::codegen(std::unique_ptr<llvm::LLVMContext> context) {
    return llvm::ConstantInt::get(
        llvm::IntegerType::get(*context, 8 * sizeof(this->value)), 
        this->value, true);
}

llvm::Value* VariableExpression::codegen(std::unique_ptr<llvm::LLVMContext> context) {
    
}