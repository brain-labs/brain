/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef DEBUG_EXPR_H
#define DEBUG_EXPR_H

#include <iostream>

#include "llvm/Transforms/Utils/BuildLibCalls.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "Expr.h"

class DebugExpr : public Expr
{
  public:
    DebugExpr() { }
    void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, ArgsOptions &argsOptions, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    void DebugDescription(int level);
    ~DebugExpr() {};
};

#endif
