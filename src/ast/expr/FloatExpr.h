/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef FLOAT_EXPR_H
#define FLOAT_EXPR_H

#include <llvm/Transforms/Utils/BuildLibCalls.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Expr.h"
#include "../general/ASTInfo.h"

/**
 * @brief The FloatExpr class behaves just like the output expression, but it
 * instead of print an integer number it will use io.c to divide the number by
 * 100 and print it.
 */
class FloatExpr : public Expr
{
public:
    FloatExpr() { ASTInfo::instance()->is_using_io_lib = true; }
    ~FloatExpr() {}
    /**
     * @brief code_gen
     * @param M
     * @param B
     * @param BreakBB
     */
    void code_gen(llvm::Module *M,
             llvm::IRBuilder<> &B,
        llvm::BasicBlock *BreakBB);
    /**
     * @brief debug_description
     * @param level
     */
    void debug_description(int level);
    /**
     * @brief ast_code_gen
     */
    void ast_code_gen();
};

#endif // FLOAT_EXPR_H
