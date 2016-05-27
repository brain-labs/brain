/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef EXPR_H
#define EXPR_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

class Expr
{
  public:
    virtual void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells) = 0;
    virtual void DebugDescription(int level) = 0;
    virtual bool UpdateExpr(char update) = 0;
    virtual ~Expr() {};
};


#endif
