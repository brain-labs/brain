/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef IF_EXPR_H
#define IF_EXPR_H

#include <vector>
#include <iostream>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Expr.h"

/**
 * @brief Class that represents the if operator in Brain.
 */
class IfExpression : public Expression
{
protected:
    std::vector<Expression *> _exprs_then;
    std::vector<Expression *> _exprs_else;
public:
    IfExpression(std::vector<Expression *> exprs_then) : _exprs_then(exprs_then) { }
    /**
     * @brief
     * @param exprs_else
     */
    void set_else(std::vector<Expression *> exprs_else) { _exprs_else = exprs_else; }
    /**
     * @brief
     * @param M
     * @param B
     * @param index
     * @param cells
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    /**
     * @brief
     */
    ExpressionType expression_category();
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
    ~IfExpression() {};
};

#endif // IF_EXPR_H

