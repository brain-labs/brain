/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef SHIFT_EXPR_H
#define SHIFT_EXPR_H

#include <iostream>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Expr.h"

/**
 * @brief Class that represents the shift operator in Brain.
 */
class ShiftExpression : public Expression
{
protected:
    int _step;
public:
    ShiftExpression(int step) : _step(step) { }
    /**
     * @brief
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
    /**
     * @brief
     * @param level
     */
    bool update_expression(char update);
    ~ShiftExpression() {};
};

#endif // SHIFT_EXPR_H
