/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef DEBUG_EXPR_H
#define DEBUG_EXPR_H

#include <iostream>

#include <llvm/Transforms/Utils/BuildLibCalls.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Expr.h"
#include "../general/ASTInfo.h"

/**
 * @brief Class that represents the debug operator in Brain.
 */
class DebugExpr : public Expr
{
public:
    DebugExpr() { ASTInfo::instance()->is_using_io_lib = true; }
    ~DebugExpr() {}
    /**
     * @brief
     * @param M
     * @param B
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

#endif // DEBUG_EXPR_H
