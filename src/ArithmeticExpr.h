/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include <iostream>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "Expr.h"

typedef enum
{
  AT_MUL,
  AT_DIV,
  AT_REM
}ArithmeticType;

class ArithmeticExpr : public Expr
{
  protected:
    ArithmeticType _type;
    std::string TypeToString();
  public:
    ArithmeticExpr(ArithmeticType type) : _type(type) { }
    void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    void DebugDescription(int level);
    bool UpdateExpr(char update);
    ~ArithmeticExpr() {};
};

#endif
