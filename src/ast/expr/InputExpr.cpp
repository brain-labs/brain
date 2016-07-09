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
  /*llvm::LLVMContext &C = M->getContext();

  llvm::Function *GetCharF = llvm::cast<llvm::Function>(
    M->getOrInsertFunction(
      "b_getchar",
      llvm::Type::getVoidTy(C), 
      llvm::Type::getInt32Ty(C),
      llvm::Type::getInt32Ty(C)->getPointerTo(),
      NULL
  ));

  llvm::Value* Args[] = { 
    B.CreateLoad(index),
    B.CreateGEP(
      B.CreatePointerCast(
        cells,
        llvm::Type::getInt32Ty(C)->getPointerTo()
      ), 
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(C), 0)
    )
  };

  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(GetCharF, ArgsArr);*/

  llvm::LLVMContext &C = M->getContext();

  llvm::Type* PutCharArgs[] = { llvm::Type::getInt32Ty(C), llvm::Type::getInt32PtrTy(C) };
  llvm::FunctionType *PutCharTy = llvm::FunctionType::get(llvm::Type::getVoidTy(C), PutCharArgs, false);
  llvm::Function *PutCharF = llvm::cast<llvm::Function>(M->getOrInsertFunction("b_getchar", PutCharTy));
  llvm::Value* Args[] = {
    B.CreateLoad(index),
    B.CreatePointerCast(cells, llvm::Type::getInt32Ty(C)->getPointerTo())
  };
  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(PutCharF, ArgsArr);

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

