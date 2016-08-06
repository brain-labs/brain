/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "ASTInfo.h"
#include "../../utils/ArgsOptions.h"

ASTInfo *ASTInfo::_instance = nullptr;
static llvm::GlobalVariable *__brain_index_ptr = nullptr;
static llvm::GlobalVariable *__brain_cells_ptr = nullptr;

ASTInfo* ASTInfo::instance()
{
    if (!ASTInfo::_instance) {
        ASTInfo::_instance = new ASTInfo();
    }
  
    return ASTInfo::_instance;
}

llvm::GlobalVariable* ASTInfo::get_index_ptr()
{
    return __brain_index_ptr;
}

llvm::GlobalVariable* ASTInfo::get_cells_ptr()
{
    return __brain_cells_ptr;
}

void ASTInfo::code_gen(llvm::Module *M, llvm::IRBuilder<> &B)
{
    llvm::LLVMContext &context = M->getContext();

    if (!__brain_index_ptr) {
        // Create global variable |brain.index|
        llvm::Type *Ty = llvm::Type::getInt32Ty(context);
        const llvm::APInt Zero = llvm::APInt(32, 0); // int32 0
        llvm::Constant *InitV = llvm::Constant::getIntegerValue(Ty, Zero);
        __brain_index_ptr = new llvm::GlobalVariable(*M,
                                                     Ty,
                                                  false, // non-constant
                      llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                                  InitV,
                                         "brain.index");
    }

    if (!__brain_cells_ptr) {
        // Create |brain.cells|
        auto *ArrTy = llvm::ArrayType::get(llvm::Type::getInt32Ty(context),
                                           ArgsOptions::instance()->get_cells_size());
        // Create a vector of _k_cells_size items equal to 0
        std::vector<llvm::Constant *> constants(ArgsOptions::instance()->get_cells_size(),
                                                B.getInt32(0));
        llvm::ArrayRef<llvm::Constant *> Constants = llvm::ArrayRef<llvm::Constant *>(constants);
        llvm::Constant *InitPtr = llvm::ConstantArray::get(ArrTy, Constants);
        __brain_cells_ptr = new llvm::GlobalVariable(*M,
                                                  ArrTy,
                                                  false, /* non-constant */
                      llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                                InitPtr,
                                          "brain.cells");
    }
}
