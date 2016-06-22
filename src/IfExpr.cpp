/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "IfExpr.h"

void IfExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::BasicBlock *EndBlock, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{

}

void IfExpr::DebugDescription(int level)
{
  std::cout << "IfExpr (THEN) [" << std::endl;
  for (std::vector<Expr *>::iterator it = _exprsThen.begin(); it != _exprsThen.end(); ++it)
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);
  }

  std::cout << std::string(level, ' ') << "]" << std::endl;

  std::cout << std::string(level, ' ') << "IfExpr (ELSE) [" << std::endl;
  for (std::vector<Expr *>::iterator it = _exprsElse.begin(); it != _exprsElse.end(); ++it)
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);
  }

  std::cout << std::string(level, ' ') << "]" << std::endl;
}

bool IfExpr::IsBranch()
{
  return true;
}
