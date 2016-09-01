/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "IfExpr.h"
#include "../general/ASTInfo.h"

void IfExpr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                      llvm::BasicBlock *BreakBB)
{
    llvm::LLVMContext &C = M->getContext();
    llvm::Function *F = B.GetInsertBlock()->getParent();

    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(C, "ThenBody", F);
    llvm::BasicBlock *ElseBB = nullptr;
    llvm::BasicBlock *ContBB = llvm::BasicBlock::Create(C, "IfCont", F);

    // Get the current cell adress
    llvm::Value *IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
    llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                                                           // Cast to int32*
                                                           llvm::Type::getInt32Ty(C)->getPointerTo()),
                                       IdxV);
    llvm::Value *NEZeroCond = B.CreateICmpNE(B.CreateLoad(CellPtr),
                                             // is cell signed int not equal
                                             // to zero?
                                             B.getInt32(0));

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
        !_exprs_else.empty()) {
        ElseBB = llvm::BasicBlock::Create(C, "ElseBody", F);
        B.CreateCondBr(NEZeroCond, ThenBB, ElseBB);
    }
    else {
        B.CreateCondBr(NEZeroCond, ThenBB, ContBB);
    }

    B.SetInsertPoint(ThenBB);
    llvm::IRBuilder<> ThenB(ThenBB);

    bool hasTerminal = false;
    for (auto& expr : _exprs_then) {
        expr->code_gen(M, ThenB, BreakBB);
        if (expr->expression_category() == ET_TERMINAL) {
            hasTerminal = true;
            break;
        }
    }

    if (!hasTerminal) {
        ThenB.CreateBr(ContBB); // uncoditional jump
    }

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_exprs_else.empty()) {
        B.SetInsertPoint(ElseBB);
        llvm::IRBuilder<> ElseB(ElseBB);
        hasTerminal = false;
        for (auto& expr : _exprs_else) {
            expr->code_gen(M, ElseB, BreakBB);
            if (expr->expression_category() == ET_TERMINAL) {
                hasTerminal = true;
                break;
            }
        }

        if (!hasTerminal) {
            ElseB.CreateBr(ContBB); // uncoditional jump
        }
    }

    B.SetInsertPoint(ContBB);
}

void IfExpr::debug_description(int level)
{
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "If Expression - THEN - if cell "
                  << " != 0 ["
                  << std::endl;
    }
    else {
        std::cout << "IfExpr (THEN) [" << std::endl;
    }

    for (auto& expr : _exprs_then) {
        std::cout << std::string(level * 2, ' ');
        expr->debug_description(level+1);
        if (expr->expression_category() == ET_TERMINAL) {
            break;
        }
    }

    std::cout << std::string(level, ' ') << "]" << std::endl;

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_exprs_else.empty()) {
        if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
            std::cout << std::string(level, ' ')
                      << "If Expression - ELSE - ["
                      << std::endl;
        }
        else {
            std::cout << std::string(level, ' ')
                      << "IfExpr (ELSE) ["
                      << std::endl;
        }

        for (auto& expr : _exprs_else) {
            std::cout << std::string(level * 2, ' ');
            expr->debug_description(level+1);
            if (expr->expression_category() == ET_TERMINAL) {
                break;
            }
        }

        std::cout << std::string(level, ' ') << "]" << std::endl;
    }
}

void IfExpr::ast_code_gen()
{
    std::cout << static_cast<char>(TT_IF_THEN);
    for (auto& expr : _exprs_then) {
        expr->ast_code_gen();
        if (expr->expression_category() == ET_TERMINAL) {
            break;
        }
    }

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_exprs_else.empty()) {
        std::cout << static_cast<char>(TT_IF_ELSE);
        for (auto& expr : _exprs_else) {
            expr->ast_code_gen();
            if (expr->expression_category() == ET_TERMINAL) {
                break;
            }
        }
    }

    std::cout << (char)TT_IF_END;
}

ExpressionType IfExpr::expression_category()
{
    return ET_BRANCH;
}

