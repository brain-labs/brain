/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "BreakExpr.h"

using namespace llvm;

void BreakExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, ArgsOptions &argsOptions, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  // it is not needed to create code gen for the BreakExpr
  // it is a terminator, so the code will stop inside the loop 
}

void BreakExpr::DebugDescription(int level)
{
  std::cout.width(level);
  std::cout << "BreakExpr" << std::endl;
}

ExpressionType BreakExpr::ExprCategory()
{
  return ET_TERMINAL;
}
