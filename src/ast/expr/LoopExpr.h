/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef LOOP_EXPR_H
#define LOOP_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <vector>
#include <iostream>

#include "Expr.h"

/**
 * @brief Enumerates the types of loops that exists in Brain.
 */
typedef enum
{
  LT_WHILE,
  LT_FOR
} LoopType;


/**
 * @brief Class that represents the loop operator in Brain.
 */
class LoopExpr : public Expr
{
protected:
    std::vector<Expr *> _exprs;
    LoopType _type;
public:
    LoopExpr(std::vector<Expr *> exprs, LoopType type) : _exprs(exprs),
        _type(type) {}
    ~LoopExpr() {}
    /**
     * @brief
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
    /**
     * @brief
     */
    void ast_code_gen();
};

#endif  // LOOP_EXPR_H
