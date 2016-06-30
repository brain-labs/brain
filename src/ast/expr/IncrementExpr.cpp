/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "IncrementExpr.h"

void IncrementExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, ArgsOptions &argsOptions, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::Value* Idxs[] = { B.getInt32(0), B.CreateLoad(index) };
  llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
  llvm::Value *CellPtr = B.CreateGEP(cells, IdxsArr);
  // Load cell value
  llvm::Value *CellV = B.CreateLoad(CellPtr);
  // Add |_step| to cell value and save the value
  B.CreateStore(B.CreateAdd(CellV, B.getInt32(_increment)), CellPtr);
}

void IncrementExpr::DebugDescription(int level)
{
  std::cout.width(level);
  std::cout << "IncrementExpr (" << _increment << ")" << std::endl;
}

bool IncrementExpr::UpdateExpr(char update)
{
  switch(update)
  {
    case '+': _increment++; return true;
    case '-': _increment--; return true;
    default : return false;
  } 
}

