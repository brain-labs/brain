/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "IfExpr.h"

void IfExpression::code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
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

    if (!_exprs_else.empty()) {
        ElseBB = llvm::BasicBlock::Create(C, "ElseBody", F);
        B.CreateCondBr(SGZeroCond, ThenBB, ElseBB);
    }
    else {
        B.CreateCondBr(SGZeroCond, ThenBB, ContBB);
    }

    B.SetInsertPoint(ThenBB);
    llvm::IRBuilder<> ThenB(ThenBB);
    for (std::vector<Expression *>::iterator it = _exprs_then.begin(); it != _exprs_then.end(); ++it) {
        if ((*it)->expression_category() == ET_TERMINAL) {
            break;
        }

        (*it)->code_gen(M, ThenB, index, cells);
    }

    ThenB.CreateBr(ContBB); // uncoditional jump

    if (!_exprs_else.empty())
    {
        B.SetInsertPoint(ElseBB);
        llvm::IRBuilder<> ElseB(ElseBB);
        for (std::vector<Expression *>::iterator it = _exprs_else.begin(); it != _exprs_else.end(); ++it) {
            if ((*it)->expression_category() == ET_TERMINAL) {
                break;
            }

            (*it)->code_gen(M, ElseB, index, cells);
        }

        ElseB.CreateBr(ContBB); // uncoditional jump
    }

    B.SetInsertPoint(ContBB);
}

void IfExpression::debug_description(int level)
{
     if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
         std::cout << "If Expression - THEN - if cell "
                   << ASTInfo::instance()->debug_index
                   << " != 0 ["
                   << std::endl;
     }
     else {
         std::cout << "IfExpression (THEN) [" << std::endl;
     }

     for (std::vector<Expression *>::iterator it = _exprs_then.begin(); it != _exprs_then.end(); ++it) {
         std::cout << std::string(level * 2, ' ');
         (*it)->debug_description(level+1);

         if ((*it)->expression_category() == ET_TERMINAL) {
             break;
         }
     }

     std::cout << std::string(level, ' ') << "]" << std::endl;

     if (!_exprs_else.empty()) {
         if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
             std::cout << std::string(level, ' ')
                       << "If Expression - ELSE - ["
                       << std::endl;
         }
         else {
             std::cout << std::string(level, ' ') << "IfExpression (ELSE) [" << std::endl;
         }

         for (std::vector<Expression *>::iterator it = _exprs_else.begin(); it != _exprs_else.end(); ++it) {
             std::cout << std::string(level * 2, ' ');
             (*it)->debug_description(level+1);

             if ((*it)->expression_category() == ET_TERMINAL) {
                 break;
             }
         }

         std::cout << std::string(level, ' ') << "]" << std::endl;
     }
}

ExpressionType IfExpression::expression_category()
{
    return ET_BRANCH;
}

