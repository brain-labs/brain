/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "IncrementExpr.h"

void IncrementExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _increment == 0) {
        return;
    }

    llvm::Value* Idxs[] = { B.getInt32(0), B.CreateLoad(index) };
    llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
    llvm::Value *CellPtr = B.CreateGEP(cells, IdxsArr);
    // Load cell value
    llvm::Value *CellV = B.CreateLoad(CellPtr);
    // Add |_step| to cell value and save the value
    B.CreateStore(B.CreateAdd(CellV, B.getInt32(_increment)), CellPtr);
}

void IncrementExpr::debug_description(int level)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _increment == 0) {
        return;
    }

    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Increment Expression - increment of "
                  << _increment
                  << " with data pointer at cell "
                  << ASTInfo::instance()->debug_index
                  << std::endl;
    }
    else
    {
        std::cout << "IncrementExpr (" << _increment << ")" << std::endl;
    }
}

bool IncrementExpr::update_expression(char update)
{
    switch (update)
    {
    case '+':
        _increment++;
        return true;
    case '-':
        _increment--;
        return true;
    default :
        return false;
    }
}

