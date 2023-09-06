#ifndef CODEGEN_H
#define CODEGEN_H


#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <map>

#include "ast.h"

class CodeGenerator : public ExpressionVisitor {
private:
    llvm::IRBuilder<> builder;
    std::unique_ptr<llvm::LLVMContext> context;
    std::map<std::string, llvm::AllocaInst*> named_values;

public:
    CodeGenerator() : builder(*context) {}
    llvm::Value* logError(const std::string& msg);

    void* visit(VariableExpression* expr) override;
    void* visit(VariableDeclarationExpression* expr) override;
    void* visit(NumberExpression* expr) override;
    void* visit(BinaryExpression* expr) override;
};


#endif //CODEGEN_H
