/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include <string>
#include "ShiftExpr.h"

void ShiftExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _step == 0 && !_jump) {
        return;
    }

    if (_jump) {
        llvm::Value* Idxs[] = { B.getInt32(0),
           B.CreateLoad(ASTInfo::instance()->get_index_ptr()) };
        llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
        llvm::Value *CellPtr = B.CreateGEP(ASTInfo::instance()->get_cells_ptr(),
            IdxsArr);
        // Load cell value
        llvm::Value *CellV = B.CreateLoad(CellPtr);

        // jump to the value
        B.CreateStore(CellV, ASTInfo::instance()->get_index_ptr());
    } else {
        // Load index value
        llvm::Value *IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
        // Add |_step| to index and save the value
        B.CreateStore(B.CreateAdd(IdxV, B.getInt32(_step)),
            ASTInfo::instance()->get_index_ptr());
    }
}

void ShiftExpr::debug_description(int level)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
        _step == 0 && !_jump) {
        return;
    }

    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        if (_jump) {
            std::cout << "Shift Expression - jump to the data pointer value"
                      << std::endl;
        } else {
            std::cout << "Shift Expression - move data pointer "
                      << _step
                      << " step(s)"
                      << std::endl;
        }
    }
    else {
        const char *step_str = std::to_string(_step).c_str();
        std::cout << "ShiftExpr ("
                  << (_jump ? "jump" : step_str) << ")"
                  << std::endl;
    }
}

void ShiftExpr::ast_code_gen()
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _step == 0 && !_jump) {
        return;
    }

    if (_jump) {
       std::cout << (char)TT_SHIFT_JUMP;
    } else if (_step > 0) {
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
    if (_jump) {
      // no optimizations when there is a jump
      return false;
    }

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
