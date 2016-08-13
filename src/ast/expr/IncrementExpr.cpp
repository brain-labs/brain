/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "IncrementExpr.h"

void IncrementExpr::code_gen(llvm::Module *M,
                        llvm::IRBuilder<> &B,
                    llvm::BasicBlock *BreakBB)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _increment == 0) {
        return;
    }

    llvm::Value* Idxs[] = { B.getInt32(0), B.CreateLoad(ASTInfo::instance()->get_index_ptr()) };
    llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
    llvm::Value *CellPtr = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(), IdxsArr);
    // Load cell value
    llvm::Value *CellV = B.CreateLoad(CellPtr);
    // Add |_increment| to cell value and save the value
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
                  << std::endl;
    }
    else
    {
        std::cout << "IncrementExpr (" << _increment << ")" << std::endl;
    }
}

void IncrementExpr::ast_code_gen()
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
        _increment == 0) {
        return;
    }
 
    if (_increment > 0) {
       for (int i = 0; i < _increment; ++i) {
           std::cout << (char)TT_INCREMENT;
       } 
    }
    else {
       for (int i = _increment; i < 0; ++i) {
           std::cout << (char)TT_DECREMENT;
       }
    }
}

bool IncrementExpr::update_expression(char update)
{
    switch (update)
    {
    case TT_INCREMENT:
        _increment++;
        return true;
    case TT_DECREMENT:
        _increment--;
        return true;
    default :
        return false;
    }
}

