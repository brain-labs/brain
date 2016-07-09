/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "InputExpr.h"

using namespace llvm;

void InputExpression::code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
    llvm::LLVMContext &C = M->getContext();
  
    // Get "scanf" function
    // i32 @scanf(i8*, ...)
    llvm::Type* ScanfArgs[] = { llvm::Type::getInt8PtrTy(C) };
    llvm::FunctionType *ScanfTy = llvm::FunctionType::get(llvm::Type::getInt32Ty(C), ScanfArgs, true /* vaarg */);
    llvm::Function *ScanfF = llvm::cast<llvm::Function>(M->getOrInsertFunction("scanf", ScanfTy));
    
    // Prepare args
    static llvm::Value *GScanfFormat = NULL;
    if (!GScanfFormat) {
	GScanfFormat = B.CreateGlobalString(" %c", "brainf.scanf.format");
    }
    llvm::Value *IntPtr = B.CreateAlloca(llvm::Type::getInt32Ty(C));
  
    // Call "scanf"
    llvm::Value* Args[] = { CAST_TO_C_STRING(GScanfFormat, B), IntPtr };
    llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
    B.CreateCall(ScanfF, ArgsArr);
    
    llvm::Value *IdxV = B.CreateLoad(index);
    llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
    // Save the new value to current cell
    B.CreateStore(B.CreateLoad(IntPtr), CellPtr);
}

void InputExpression::debug_description(int level)
{
    std::cout.width(level);
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
	std::cout << "Input Expression - read char with data pointer at cell " 
		  << ASTInfo::instance()->debug_index
		  << std::endl;
    }
    else {
	std::cout << "InputExpression" << std::endl;
    }
}

