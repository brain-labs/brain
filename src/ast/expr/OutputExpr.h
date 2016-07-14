/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef OUTPUT_EXPR_H
#define OUTPUT_EXPR_H

#include <llvm/Transforms/Utils/BuildLibCalls.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Expression.h"

/**
 * @brief Class that represents the output operator in Brain.
 */
class OutputExpression : public Expression
{
public:
    OutputExpression();
    ~OutputExpression();
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

#endif  // OUTPUT_EXPR_H
