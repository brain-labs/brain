/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "LoopExpr.h"

void LoopExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  
  // Create a basic block for loop
  llvm::Function *F = B.GetInsertBlock()->getParent();
  llvm::BasicBlock *StartBB = llvm::BasicBlock::Create(C, "LoopStart", F);
  
  llvm::Value *IdxV = nullptr; 
  llvm::Value *CellPtr = nullptr; 
  llvm::Value *CounterV = nullptr;
  if (_type == LT_FOR)
  {
    // Get the current cell adress
    IdxV = B.CreateLoad(index);
    CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
    CounterV = B.CreateAlloca(llvm::Type::getInt32Ty(C), 0, "counter");
    B.CreateStore(B.CreateLoad(CellPtr), CounterV);
  }

  B.CreateBr(StartBB);
  
  B.SetInsertPoint(StartBB);
  llvm::IRBuilder<> StartB(StartBB);
  
  // Enter the block ("LoopBody") if current cell value > 0, else skip the loop (i.e.: go to "LoopEnd")
  llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(C, "LoopBody", F);
  llvm::BasicBlock *EndBB = llvm::BasicBlock::Create(C, "LoopEnd", F);
  
  llvm::Value *SGZeroCond = nullptr;
  if (_type == LT_FOR)
  {
    SGZeroCond = StartB.CreateICmpSGT(StartB.CreateLoad(CounterV),
                                           StartB.getInt32(0)); // is cell Signed Int Greater than Zero?
  }
  else
  {
    // Get the current cell adress
    IdxV = B.CreateLoad(index);
    CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
    SGZeroCond = StartB.CreateICmpSGT(StartB.CreateLoad(CellPtr),
                                           StartB.getInt32(0)); // is cell Signed Int Greater than Zero?
  }

  StartB.CreateCondBr(SGZeroCond, LoopBB, EndBB);
  
  B.SetInsertPoint(LoopBB);
  llvm::IRBuilder<> LoopB(LoopBB);
  // Recursively generate code (into "LoopBody" block)
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it)
  {
    (*it)->CodeGen(M, LoopB, EndBB, index, cells);
  }

  if (_type == LT_FOR)
  {
    LoopB.CreateStore(LoopB.CreateAdd(LoopB.CreateLoad(CounterV), LoopB.getInt32(-1)), CounterV);
  }
  
  LoopB.CreateBr(StartBB); // Restart loop (will next exit if current cell value > 0)
  
  B.SetInsertPoint(EndBB);
}

void LoopExpr::DebugDescription(int level)
{
  std::string openedBrackets = (_type == LT_FOR) ? "{" : "[";
  std::string closedBrackets = (_type == LT_FOR) ? "}" : "]";  
 
  std::cout << "LoopExpr: " << openedBrackets << std::endl;
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it)
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);
  }
  std::cout << std::string(level, ' ') << closedBrackets << std::endl;
}

