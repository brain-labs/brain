/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef SHIFT_EXPR_H
#define SHIFT_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Expr.h"

/**
 * @brief Class that represents the shift operator in Brain.
 */
class ShiftExpr : public Expr
{
protected:
    /// steps to jump
    int _step;

    /// should it jump?
    bool _jump;
public:
    ShiftExpr(int step) : _step(step), _jump(false) {}
    ShiftExpr() : _step(0), _jump(true) {}
    ~ShiftExpr() {}
    /**
     * @brief Generates the IR (Intermediate Representation) code to be
     * executed by llvm.
     * @param M A pointer to the Brain's module.
     * @param B A reference to the Brain's IR builder.
     * @param BreakBB A pointer to the Brain's basic block.
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                  llvm::BasicBlock *BreakBB);
    /**
     * @brief Prints debug information when Brain's compiler has the active
     * flags: -v | -emit-ast.
     * @param level The width used to display the debug information (to mimic
     * identation).
     */
    void debug_description(int level);
    /**
     * @brief Method for the reverse code generation from the AST. It prints
     * out to the stdout the token itself.
     */
    void ast_code_gen();
    /**
     * @brief Virtual method for updating the AST exprs.
     * @param update The char whose expression will be updated.
     */
    bool update_expression(char update);
};

#endif  // SHIFT_EXPR_H
