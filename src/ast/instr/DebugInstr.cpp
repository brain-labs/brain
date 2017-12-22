/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "DebugInstr.h"

void DebugInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                         llvm::BasicBlock *BreakBB)
{
  llvm::LLVMContext &C = M->getContext();
  llvm::Type* DebugArgs[] = { llvm::Type::getInt32Ty(C),
                              llvm::Type::getInt32PtrTy(C),
                              llvm::Type::getInt32Ty(C) };
  llvm::FunctionType *DebugTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C), DebugArgs, false);
  llvm::Function *DebugF = llvm::cast<llvm::Function>(M->getOrInsertFunction("b_debug", DebugTy));
  llvm::Value* Args[] = {
    B.CreateLoad(ASTInfo::instance()->get_index_ptr()),
    B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                        llvm::Type::getInt32Ty(C)->getPointerTo()),
    B.CreateLoad(ASTInfo::instance()->get_cells_size())
  };
  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(DebugF, ArgsArr);
}

void DebugInstr::debug_description(int level)
{
  std::cout.width(level);
  if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
    std::cout << "Debug Instression"
              << std::endl;
  }
  else {
    std::cout << "DebugInstr" << std::endl;
  }
}

void DebugInstr::ast_code_gen()
{
    std::cout << (char)TT_DEBUG;
}
