/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "InputInstr.h"

void InputInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Type* GetCharArgs[] = { ASTInfo::instance()->get_cell_type(C),
                                  ASTInfo::instance()->get_cell_ptr_type(C),
                                  llvm::Type::getInt32Ty(C) };
    llvm::FunctionType *GetCharTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C),
                                                            GetCharArgs, false);
    llvm::Function *GetCharF = llvm::cast<llvm::Function>(
        M->getOrInsertFunction(
            "b_getchar_" + std::to_string(ArgsOptions::instance()->get_cell_bitsize()),
            GetCharTy
        )
    );

    llvm::Value* Args[] = {
        B.CreateLoad(ASTInfo::instance()->get_index_ptr()),
        B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                            ASTInfo::instance()->get_cell_type(C)->getPointerTo()),
        B.CreateLoad(ASTInfo::instance()->get_cells_size())
    };

    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(GetCharF, ArgsArr);
}

void InputInstr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Input Instruction - read char"
                  << std::endl;
    }
    else {
        std::cout << "InputInstr" << std::endl;
    }
}

void InputInstr::ast_code_gen()
{
    std::cout << (char)TT_INPUT;
}
