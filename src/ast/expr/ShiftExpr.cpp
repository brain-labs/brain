/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "ShiftExpr.h"

void ShiftExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _step == 0) {
        return;
    }

    // Load index value
    llvm::Value *IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
    // Add |_step| to index and save the value
    B.CreateStore(B.CreateAdd(IdxV, B.getInt32(_step)), ASTInfo::instance()->get_index_ptr());
}

void ShiftExpr::debug_description(int level)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _step == 0) {
        return;
    }

    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Shift Expression - move data pointer "
                  << _step
                  << " step(s)"
                  << std::endl;
    }
    else {
        std::cout << "ShiftExpr (" << _step << ")" << std::endl;
    }
}

void ShiftExpr::ast_code_gen()
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _step == 0) {
        return;
    }

    if (_step > 0) {
       for (int i = 0; i < _step; ++i) {
           std::cout << (char)TT_SHIFT_RIGHT;
       }
    }
    else {
       for (int i = _step; i < 0; ++i) {
           std::cout << (char)TT_SHIFT_LEFT;
       }
    }
}

bool ShiftExpr::update_expression(char update)
{
    switch(update)
    {
    case TT_SHIFT_RIGHT:
        _step++;
        return true;
    case TT_SHIFT_LEFT:
        _step--;
        return true;
    default :
        return false;
    }
}

