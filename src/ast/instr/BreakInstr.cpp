/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "BreakInstr.h"
#include "../../utils/ArgsOptions.h"

void BreakInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    if (BreakBB) {
        B.CreateBr(BreakBB);
    }
}

void BreakInstr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Break Instruction"
                  << std::endl;
    }
    else {
        std::cout << "BreakInstr" << std::endl;
    }
}

void BreakInstr::ast_code_gen()
{
    std::cout << (char)TT_BREAK;
}

InstructionType BreakInstr::instruction_category()
{
    return ET_TERMINAL;
}
