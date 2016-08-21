/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "FloatExpr.h"

void FloatExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Type* PutCharArgs[] = { llvm::Type::getInt32Ty(C),
                                  llvm::Type::getInt32PtrTy(C) };

    llvm::FunctionType *FloatPrintTy =
            llvm::FunctionType::get(llvm::Type::getVoidTy(C), PutCharArgs,
                                    false);
    llvm::Function *FloatPrintF =
            llvm::cast<llvm::Function>(M->getOrInsertFunction("b_float_print",
                                                              FloatPrintTy));

    // Creating the arguments which will be passed to the called function in
    // io.c
    llvm::Value* Args[] = {
        B.CreateLoad(ASTInfo::instance()->get_index_ptr()),
        B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                            llvm::Type::getInt32Ty(C)->getPointerTo())
    };

    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(FloatPrintF, ArgsArr);
}

void FloatExpr::ast_code_gen()
{
    std::cout << (char)TT_FLOAT;
}

void FloatExpr::debug_description(int level)
{
    std::cout.width(level);

    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Float Expression - print out float numbers" << std::endl;
    }
    else {
        std::cout << "FloatExpr" << std::endl;
    }
}
