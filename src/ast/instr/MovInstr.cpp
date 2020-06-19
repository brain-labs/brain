/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2018.
 */

#include "MovInstr.h"
#include "../../utils/ArgsOptions.h"
#include "../general/ASTInfo.h"

void MovInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    llvm::Value *IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
    llvm::Value* Idxs[] = { B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0),
                            IdxV };
    llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
    llvm::Value *CellPtr = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
                                       IdxsArr);
    // Load current cell value
    llvm::Value *CellV = B.CreateLoad(CellPtr);

    // Load index value - 1
    llvm::Value *IdxPreV = B.CreateAdd(IdxV,
                                       B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), -1));
    llvm::Value* Idxs2[] = { B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0),
                             IdxPreV };
    llvm::ArrayRef<llvm::Value *> IdxsArr2(Idxs2);
    llvm::Value *CellPtr2 = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
                                        IdxsArr2);
    // Load previous cell value
    llvm::Value *CellV2 = B.CreateLoad(CellPtr2);

    llvm::Value* IdxsFinal[] = { B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0),
                            CellV };
    llvm::ArrayRef<llvm::Value *> IdxsArrFinal(IdxsFinal);
    llvm::Value *CellPtrFinal = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
                                       IdxsArrFinal);

    B.CreateStore(CellV2, CellPtrFinal);
}

void MovInstr::ast_code_gen()
{
    std::cout << (char)TT_MOV;
}

void MovInstr::debug_description(int level)
{
    std::cout.width(level);

    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Mov Instruction - move data on the tape" << std::endl;
    }
    else {
        std::cout << "MovInstr" << std::endl;
    }
}