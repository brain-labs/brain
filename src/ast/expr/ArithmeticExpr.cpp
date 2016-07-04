/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "ArithmeticExpr.h"

void ArithmeticExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::Value *IdxV = B.CreateLoad(index);  
  llvm::Value* Idxs[] = { B.getInt32(0), IdxV };
  llvm::ArrayRef<llvm::Value *> IdxsArr(Idxs);
  llvm::Value *CellPtr = B.CreateGEP(cells, IdxsArr);
  // Load cell value
  llvm::Value *CellV = B.CreateLoad(CellPtr);

   // Load index value - 1
  llvm::Value *IdxPreV = B.CreateAdd(IdxV, B.getInt32(-1));
  llvm::Value* Idxs2[] = { B.getInt32(0), IdxPreV };
  llvm::ArrayRef<llvm::Value *> IdxsArr2(Idxs2);
  llvm::Value *CellPtr2 = B.CreateGEP(cells, IdxsArr2);
  // Load cell value
  llvm::Value *CellV2 = B.CreateLoad(CellPtr2);

  switch (_type)
  {
    case AT_MUL:
    {
      // Multiplies the value at the current index with the value at the current index - 1 and
      // stores it at the current index
      B.CreateStore(B.CreateMul(CellV, CellV2), CellPtr);
      break;
    }
    case AT_DIV:
    {
      B.CreateStore(B.CreateSDiv(CellV, CellV2), CellPtr);
      break;
    }
    case AT_REM:
    {
      B.CreateStore(B.CreateSRem(CellV, CellV2), CellPtr);
      break;
    }
  }
}

void ArithmeticExpr::DebugDescription(int level)
{
  std::cout.width(level);
  if (ArgsOptions::instance()->hasOption(BO_IS_VERBOSE))
  {
    std::cout << "Arithmetic Expression - " << TypeToString() 
              << " with the cells " 
              << ASTInfo::instance()->debugIndex
              << " and "
              << (ASTInfo::instance()->debugIndex - 1)
              << " with data pointer at cell " 
              << ASTInfo::instance()->debugIndex
              << std::endl;
  }
  else
  {
    std::cout << "ArithmeticExpr ( " << TypeToString() << " )" << std::endl;
  }
}

std::string ArithmeticExpr::TypeToString()
{
  switch (_type)
  {
    case AT_MUL:
    {
      return "multiplication";
    }
    case AT_DIV:
    {
      return "division";
    }
    case AT_REM:
    {
      return "remainder";
    }
  }
}

