/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef INCREMENT_EXPR_H
#define INCREMENT_EXPR_H

#include <iostream>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Expression.h"

/**
 * @brief Class that represent the increment operator in Brain.
 */
class IncrementExpression : public Expression
{
protected:
    int _increment;
public:
    explicit IncrementExpression(int increment) : _increment(increment) { }
    ~IncrementExpression();
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
     * @param update
     */
    bool update_expression(char update);
};

#endif  // INCREMENT_EXPR_H
