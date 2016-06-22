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


#ifndef __cast_capital__ 
  #define CAST_TO_C_STRING castToCStr
#else
  #define CAST_TO_C_STRING CastToCStr
#endif

class Expr
{
  public:
    virtual void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells) = 0;
    virtual void DebugDescription(int level) = 0;
    virtual bool UpdateExpr(char update) { return false; }
    virtual bool IsBranch() { return false; }
    virtual bool IsTerminator() { return false; } 
    virtual ~Expr() {};
};

#endif
