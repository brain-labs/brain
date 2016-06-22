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

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "Expr.h"

class IfExpr : public Expr
{
  protected:
    std::vector<Expr *> _exprsThen;
    std::vector<Expr *> _exprsElse;
  public:
    IfExpr(std::vector<Expr *> exprsThen) : _exprsThen(exprsThen) { }
    void SetElse(std::vector<Expr *> exprsElse) { _exprsElse = exprsElse; } 
    void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    bool IsBranch();
    void DebugDescription(int level);
    ~IfExpr() {};
};

#endif

