/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "InputExpr.h"

void InputExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Type* GetCharArgs[] = { llvm::Type::getInt32Ty(C), llvm::Type::getInt32PtrTy(C) };
    llvm::FunctionType *GetCharTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C), GetCharArgs, false);
    llvm::Function *GetCharF = llvm::cast<llvm::Function>(M->getOrInsertFunction("b_getchar", GetCharTy));
    llvm::Value* Args[] = {
        B.CreateLoad(index),
        B.CreatePointerCast(cells, llvm::Type::getInt32Ty(C)->getPointerTo())
    };
    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(GetCharF, ArgsArr);
}

void InputExpr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Input Expression - read char with data pointer at cell " 
                  << ASTInfo::instance()->debug_index
                  << std::endl;
    }
    else {
        std::cout << "InputExpr" << std::endl;
    }
}

