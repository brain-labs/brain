/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "OutputExpr.h"

using namespace llvm;

void OutputExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  
  // Get "printf" function
  // i32 @printf(i8*, ...)
  llvm::Type* PrintfArgs[] = { llvm::Type::getInt8PtrTy(C) };
  llvm::FunctionType *PrintfTy = llvm::FunctionType::get(llvm::Type::getInt32Ty(C), PrintfArgs, true /* vaarg */);
  llvm::Function *PrintfF = llvm::cast<llvm::Function>(M->getOrInsertFunction("printf", PrintfTy));
  
  // Prepare args
  static llvm::Value *GPrintfFormat = NULL;
  if (!GPrintfFormat) {
    GPrintfFormat = B.CreateGlobalString("%c", "brainf.printf.format");
  }
  llvm::Value *IdxV = B.CreateLoad(index);
  llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
  
  // Call "printf"
  llvm::Value* Args[] = { CAST_TO_C_STRING(GPrintfFormat, B), B.CreateLoad(CellPtr) };
  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(PrintfF, ArgsArr);
}

void OutputExpr::DebugDescription(int level)
{
  std::cout.width(level);
  std::cout << "OutputExpr" << std::endl;
}

