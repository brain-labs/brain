/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "DebugExpr.h"

void DebugExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B)
{
  llvm::LLVMContext &C = M->getContext();
  llvm::Type* DebugArgs[] = { llvm::Type::getInt32Ty(C), llvm::Type::getInt32PtrTy(C) };
  llvm::FunctionType *DebugTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C), DebugArgs, false);
  llvm::Function *DebugF = llvm::cast<llvm::Function>(M->getOrInsertFunction("b_debug", DebugTy));
  llvm::Value* Args[] = {
    B.CreateLoad(ASTInfo::instance()->get_index_ptr()),
    B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(), llvm::Type::getInt32Ty(C)->getPointerTo())
  };
  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(DebugF, ArgsArr);
}

void DebugExpr::debug_description(int level)
{
  std::cout.width(level);
  if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
    std::cout << "Debug Expression" 
              << std::endl;
  }
  else {
    std::cout << "DebugExpr" << std::endl;
  }
}

void DebugExpr::ast_code_gen()
{
    std::cout << (char)TT_DEBUG;
}
