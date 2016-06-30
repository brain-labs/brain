/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "IfExpr.h"

void IfExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, ArgsOptions &argsOptions, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  llvm::Function *F = B.GetInsertBlock()->getParent();
  
  llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(C, "ThenBody", F);
  llvm::BasicBlock *ElseBB = nullptr;
  llvm::BasicBlock *ContBB = llvm::BasicBlock::Create(C, "IfCont", F);

  // Get the current cell adress
  llvm::Value *IdxV = B.CreateLoad(index);
  llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
  llvm::Value *SGZeroCond = B.CreateICmpSGT(B.CreateLoad(CellPtr),
                                           B.getInt32(0)); // is cell Signed Int Greater than Zero?
  
  if (!_exprsElse.empty())
  {
    ElseBB = llvm::BasicBlock::Create(C, "ElseBody", F);
    B.CreateCondBr(SGZeroCond, ThenBB, ElseBB);
  }
  else
  {
    B.CreateCondBr(SGZeroCond, ThenBB, ContBB);
  }

  B.SetInsertPoint(ThenBB);
  llvm::IRBuilder<> ThenB(ThenBB);
  for (std::vector<Expr *>::iterator it = _exprsThen.begin(); it != _exprsThen.end(); ++it)
  {
    if ((*it)->ExprCategory() == ET_TERMINAL)
      break;

    (*it)->CodeGen(M, ThenB, argsOptions, index, cells);
  }
  
  ThenB.CreateBr(ContBB); // uncoditional jump

  if (!_exprsElse.empty()) 
  {
    B.SetInsertPoint(ElseBB);
    llvm::IRBuilder<> ElseB(ElseBB);
    for (std::vector<Expr *>::iterator it = _exprsElse.begin(); it != _exprsElse.end(); ++it)
    {
      if ((*it)->ExprCategory() == ET_TERMINAL)
        break;

      (*it)->CodeGen(M, ElseB, argsOptions, index, cells);
    }

    ElseB.CreateBr(ContBB); // uncoditional jump
  }

  B.SetInsertPoint(ContBB);
}

void IfExpr::DebugDescription(int level)
{
  std::cout << "IfExpr (THEN) [" << std::endl;
  for (std::vector<Expr *>::iterator it = _exprsThen.begin(); it != _exprsThen.end(); ++it)
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);

    if ((*it)->ExprCategory() == ET_TERMINAL)
      break;
  }

  std::cout << std::string(level, ' ') << "]" << std::endl;

  if (!_exprsElse.empty())
  {
    std::cout << std::string(level, ' ') << "IfExpr (ELSE) [" << std::endl;
    for (std::vector<Expr *>::iterator it = _exprsElse.begin(); it != _exprsElse.end(); ++it)
    {
      std::cout << std::string(level * 2, ' ');
      (*it)->DebugDescription(level+1);

      if ((*it)->ExprCategory() == ET_TERMINAL)
        break;
    }

    std::cout << std::string(level, ' ') << "]" << std::endl;
  }
}

ExpressionType IfExpr::ExprCategory()
{
  return ET_BRANCH;
}

