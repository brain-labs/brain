/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "ShiftExpr.h"

void ShiftExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::GlobalVariable *index,
                         llvm::GlobalVariable *cells)
{
    // Load index value
    llvm::Value *IdxV = B.CreateLoad(index);
    // Add |_step| to index and save the value
    B.CreateStore(B.CreateAdd(IdxV, B.getInt32(_step)), index);
}

void ShiftExpr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Shift Expression - move data pointer from "
                  << ASTInfo::instance()->debug_index
                  << " to "
                  << ASTInfo::instance()->debug_index + _step
                  << " - "
                  << _step
                  << " step(s)"
                  << std::endl;
    }
    else {
        std::cout << "ShiftExpr (" << _step << ")" << std::endl;
    }

    ASTInfo::instance()->debug_index += _step;
}

bool ShiftExpr::update_expression(char update)
{
    switch(update)
    {
    case '>':
        _step++;
        return true;
    case '<':
        _step--;
        return true;
    default :
        return false;
    }
}

