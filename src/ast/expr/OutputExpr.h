/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef OUTPUT_EXPR_H
#define OUTPUT_EXPR_H

#include <llvm/Transforms/Utils/BuildLibCalls.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Expr.h"
#include "../general/ASTInfo.h"

/**
 * @brief Class that represents the output operator in Brain.
 */
class OutputExpr : public Expr
{
public:
    OutputExpr() { ASTInfo::instance()->is_using_io_lib = true; }
    ~OutputExpr() {}
    /**
     * @brief code_gen
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

#endif  // OUTPUT_EXPR_H
