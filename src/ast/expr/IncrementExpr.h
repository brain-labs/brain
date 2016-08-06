/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef INCREMENT_EXPR_H
#define INCREMENT_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Expr.h"

/**
 * @brief Class that represent the increment operator in Brain.
 */
class IncrementExpr : public Expr
{
protected:
    int _increment;
public:
    explicit IncrementExpr(int increment) : _increment(increment) { }
    ~IncrementExpr() { }
    /**
     * @brief
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                  llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
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
    /**
     * @brief
     */
    void ast_code_gen();
};

#endif  // INCREMENT_EXPR_H
