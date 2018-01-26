/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "FloatInstr.h"

void FloatInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Type* PutCharArgs[] = { ASTInfo::instance()->get_cell_type(C),
                                  ASTInfo::instance()->get_cell_ptr_type(C),
                                  llvm::Type::getInt32Ty(C) };

    llvm::FunctionType *FloatPrintTy =
            llvm::FunctionType::get(llvm::Type::getVoidTy(C), PutCharArgs,
                                    false);
    llvm::Function *FloatPrintF = llvm::cast<llvm::Function>(
        M->getOrInsertFunction(
            "b_float_print_" + std::to_string(ArgsOptions::instance()->get_cell_bitsize()),
            FloatPrintTy
        )
    );

    // Creating the arguments which will be passed to the called function in
    // io.c
    llvm::Value* Args[] = {
        B.CreateLoad(ASTInfo::instance()->get_index_ptr()),
        B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                            ASTInfo::instance()->get_cell_type(C)->getPointerTo()),
        B.CreateLoad(ASTInfo::instance()->get_cells_size())
    };

    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(FloatPrintF, ArgsArr);
}

void FloatInstr::ast_code_gen()
{
    std::cout << (char)TT_FLOAT;
}

void FloatInstr::debug_description(int level)
{
    std::cout.width(level);

    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Float Instruction - print out float numbers" << std::endl;
    }
    else {
        std::cout << "FloatInstr" << std::endl;
    }
}
