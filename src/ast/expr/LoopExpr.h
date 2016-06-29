/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef LOOP_EXPR_H
#define LOOP_EXPR_H

#include <vector>
#include <iostream>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "Expr.h"

typedef enum
{
  LT_WHILE,
  LT_FOR
}LoopType;

class LoopExpr : public Expr
{
  protected:
    std::vector<Expr *> _exprs;
    LoopType _type;
  public:
    LoopExpr(std::vector<Expr *> exprs, LoopType type) : _exprs(exprs), _type(type) { }
    void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    void DebugDescription(int level);
    ~LoopExpr() {};
};

#endif

