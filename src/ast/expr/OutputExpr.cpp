/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "OutputExpr.h"

void OutputExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                          llvm::GlobalVariable *index,
                          llvm::GlobalVariable *cells)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Type* PutCharArgs[] = { llvm::Type::getInt32Ty(C), llvm::Type::getInt32PtrTy(C) };
    llvm::FunctionType *PutCharTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C), PutCharArgs, false);
    llvm::Function *PutCharF = llvm::cast<llvm::Function>(M->getOrInsertFunction("b_putchar", PutCharTy));
    llvm::Value* Args[] = {
        B.CreateLoad(index),
        B.CreatePointerCast(cells, llvm::Type::getInt32Ty(C)->getPointerTo())
    };
    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(PutCharF, ArgsArr);
}

void OutputExpr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Output Expression - print out char with data pointer at cell "
                  << ASTInfo::instance()->debug_index
                  << std::endl;
    }
    else {
        std::cout << "OutputExpr" << std::endl;
    }
}

void OutputExpr::ast_code_gen()
{
    std::cout << (char)TT_OUTPUT;
}
