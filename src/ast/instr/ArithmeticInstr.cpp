
/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "ArithmeticInstr.h"
#include "../../utils/ArgsOptions.h"
#include "../general/ASTInfo.h"

void ArithmeticInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                              llvm::BasicBlock *BreakBB)
{
    llvm::Value *IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
    llvm::Value* Idxs[] = { B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0),
                            IdxV };
    llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
    llvm::Value *CellPtr = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
                                       IdxsArr);
    // Load cell value
    llvm::Value *CellV = B.CreateLoad(CellPtr);

    // Load index value - 1
    llvm::Value *IdxPreV = B.CreateAdd(IdxV,
                                       B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), -1));
    llvm::Value* Idxs2[] = { B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0),
                             IdxPreV };
    llvm::ArrayRef<llvm::Value *> IdxsArr2(Idxs2);
    llvm::Value *CellPtr2 = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
                                        IdxsArr2);
    // Load cell value
    llvm::Value *CellV2 = B.CreateLoad(CellPtr2);

    switch (_type)
    {
    case AT_MUL:
        // Multiplies the value at the current index with the value
        // at index - 1 and stores it at the current index.
        B.CreateStore(B.CreateMul(CellV, CellV2), CellPtr);
        break;
    case AT_DIV:
        // Divides the value at the current index with the value
        // at index - 1 and stores it at the current index.
        B.CreateStore(B.CreateSDiv(CellV, CellV2), CellPtr);
        break;
    case AT_REM:
        // Divides the value at the current index with the value
        // at index - 1 and stores the remainder at the current index.
        B.CreateStore(B.CreateSRem(CellV, CellV2), CellPtr);
        break;
    }
}

void ArithmeticInstr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Arithmetic Instruction - " << type_to_string()
                  << std::endl;
    }
    else {
        std::cout << "ArithmeticInstr ( " << type_to_string() << " )"
                  << std::endl;
    }
}

void ArithmeticInstr::ast_code_gen()
{
    char arithmetic_char = '\0';

    switch (_type)
    {
    case AT_MUL:
        arithmetic_char = TT_MUL;
        break;
    case AT_DIV:
        arithmetic_char = TT_DIV;
        break;
    case AT_REM:
        arithmetic_char = TT_REM;
        break;
    }

    std::cout << (char)arithmetic_char;
}

std::string ArithmeticInstr::type_to_string()
{
    std::string type = "";

    switch (_type)
    {
    case AT_MUL:
        type = "multiplication";
        break;
    case AT_DIV:
        type =  "division";
        break;
    case AT_REM:
        type = "remainder";
        break;
    }

    return type;
}
