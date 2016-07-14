/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef LOOP_EXPR_H
#define LOOP_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <vector>
#include <iostream>

#include "Expression.h"

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
class LoopExpression : public Expression
{
protected:
    std::vector<Expression *> _exprs;
    LoopType _type;
public:
    LoopExpression(std::vector<Expression *> exprs, LoopType type) : _exprs(exprs), _type(type) { }
    ~LoopExpression();
    /**
     * @brief
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
};

#endif  // LOOP_EXPR_H
