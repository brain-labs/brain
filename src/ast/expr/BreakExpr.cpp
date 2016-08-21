/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "BreakExpr.h"

void BreakExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
    if (BreakBB) {
        B.CreateBr(BreakBB);
    }
}

void BreakExpr::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Break Expression"
                  << std::endl;
    }
    else {
        std::cout << "BreakExpr" << std::endl;
    }
}

void BreakExpr::ast_code_gen()
{
    std::cout << (char)TT_BREAK;
}

ExpressionType BreakExpr::expression_category()
{
    return ET_TERMINAL;
}
