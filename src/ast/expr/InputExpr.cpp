/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "InputExpr.h"

using namespace llvm;

void InputExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  
  llvm::Function *GetCharF = llvm::cast<llvm::Function>(M->getOrInsertFunction("brain_getchar", llvm::Type::getInt32Ty(C), NULL));
  llvm::CallInst *GetCharCall = B.CreateCall(GetCharF);
  GetCharCall->setTailCall(false);
  llvm::Value *IntPtr = GetCharCall;
	
  llvm::Value *IdxV = B.CreateLoad(index);
  llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
  // Save the new value to current cell
  B.CreateStore(IntPtr, CellPtr);
}

void InputExpr::DebugDescription(int level)
{
  std::cout.width(level);
  if (ArgsOptions::instance()->hasOption(BO_IS_VERBOSE))
  {
    std::cout << "Input Expression - read char with data pointer at cell " 
              << ASTInfo::instance()->debugIndex
              << std::endl;
  }
  else
  {
    std::cout << "InputExpr" << std::endl;
  }
}

