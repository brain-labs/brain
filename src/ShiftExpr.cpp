/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "ShiftExpr.h"

void ShiftExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  // Load index value
  llvm::Value *IdxV = B.CreateLoad(index);
  // Add |_step| to index and save the value
  B.CreateStore(B.CreateAdd(IdxV, B.getInt32(_step)), index);
}

void ShiftExpr::DebugDescription(int level)
{
}
