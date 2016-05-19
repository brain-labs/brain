/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "LoopExpr.h"

void LoopExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  
  // Create a basic block for loop
  llvm::Function *F = B.GetInsertBlock()->getParent();
  llvm::BasicBlock *StartBB = llvm::BasicBlock::Create(C, "LoopStart", F);
  B.CreateBr(StartBB);
  
  B.SetInsertPoint(StartBB);
  llvm::IRBuilder<> StartB(StartBB);
  
  // Enter the block ("LoopBody") if current cell value > 0, else skip the loop (i.e.: go to "LoopEnd")
  llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(C, "LoopBody", F);
  llvm::BasicBlock *EndBB = llvm::BasicBlock::Create(C, "LoopEnd", F);
  
  // Get the current cell adress
  llvm::Value *IdxV = B.CreateLoad(index);
  llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
  llvm::Value *SGZeroCond = StartB.CreateICmpSGT(StartB.CreateLoad(CellPtr),
                                           StartB.getInt32(0)); // is cell Signed Int Greater than Zero?
  StartB.CreateCondBr(SGZeroCond, LoopBB, EndBB);
  
  B.SetInsertPoint(LoopBB);
  llvm::IRBuilder<> LoopB(LoopBB);
  // Recursively generate code (into "LoopBody" block)
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it)
  {
    (*it)->CodeGen(M, LoopB, index, cells);
  }
  LoopB.CreateBr(StartBB); // Restart loop (will next exit if current cell value > 0)
  
  B.SetInsertPoint(EndBB);
}

void LoopExpr::DebugDescription(int level)
{
  std::cout << "LoopExpr: [" << std::endl;
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it)
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);
  }
  std::cout << std::string(level, ' ') << "]" << std::endl;
}

bool LoopExpr::UpdateExpr(char update)
{
  return false;
}

EXPR_TYPE LoopExpr::ExprType()
{
  return ET_LOOP;
}
