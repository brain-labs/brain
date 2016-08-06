/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
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
class IfExpr : public Expr
{
protected:
    ///
    std::vector<Expr *> _exprs_then;
    ///
    std::vector<Expr *> _exprs_else;
public:
    IfExpr(std::vector<Expr *> exprs_then) : _exprs_then(exprs_then) {}
    ~IfExpr() {}
    /**
     * @brief
     * @param exprs_else
     */
    void set_else(std::vector<Expr *> exprs_else) { _exprs_else = exprs_else; }
    /**
     * @brief
     * @param M
     * @param B
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @brief
     */
    ExpressionType expression_category();
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

#endif // IF_EXPR_H

