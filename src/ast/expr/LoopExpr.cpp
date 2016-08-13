/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "LoopExpr.h"
#include "../../utils/ArgsOptions.h"

void LoopExpr::code_gen(llvm::Module *M,
                   llvm::IRBuilder<> &B,
              llvm::BasicBlock *BreakBB)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _exprs.empty()) {
        return;
    }

    llvm::LLVMContext &C = M->getContext();

    // Create a basic block for loop
    llvm::Function *F = B.GetInsertBlock()->getParent();
    llvm::BasicBlock *StartBB = llvm::BasicBlock::Create(C, "LoopStart", F);

    llvm::Value *IdxV = nullptr;
    llvm::Value *CellPtr = nullptr;
    llvm::Value *CounterV = nullptr;

    if (_type == LT_FOR) {
        // Get the current cell adress
        IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
        CellPtr = B.CreateGEP(B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                                                  llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                              IdxV);
        CounterV = B.CreateAlloca(llvm::Type::getInt32Ty(C), 0, "counter");
        B.CreateStore(B.CreateLoad(CellPtr), CounterV);
    }

    B.CreateBr(StartBB);

    B.SetInsertPoint(StartBB);
    llvm::IRBuilder<> StartB(StartBB);

    // Enter the block ("LoopBody") if current cell value > 0, else skip the loop (i.e.: go to "LoopEnd")
    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(C, "LoopBody", F);
    llvm::BasicBlock *EndBB = llvm::BasicBlock::Create(C, "LoopEnd", F);

    llvm::Value *NEZeroCond = nullptr;
    if (_type == LT_FOR) {
        NEZeroCond = StartB.CreateICmpNE(StartB.CreateLoad(CounterV),
                                         StartB.getInt32(0)); // is cell Signed Int Not Equal to Zero?
    }
    else {
        // Get the current cell adress
        IdxV = B.CreateLoad(ASTInfo::instance()->get_index_ptr());
        CellPtr = B.CreateGEP(B.CreatePointerCast(ASTInfo::instance()->get_cells_ptr(),
                                                  llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                              IdxV);
        NEZeroCond = StartB.CreateICmpNE(StartB.CreateLoad(CellPtr),
                                          StartB.getInt32(0)); // is cell Signed Int Not Equal to Zero?
    }

    StartB.CreateCondBr(NEZeroCond, LoopBB, EndBB);

    B.SetInsertPoint(LoopBB);
    llvm::IRBuilder<> LoopB(LoopBB);
    bool hasTerminal = false;
    // Recursively generate code (into "LoopBody" block)
    for (auto& expr : _exprs) {
        expr->code_gen(M, LoopB, EndBB);
        if (expr->expression_category() == ET_TERMINAL) {
            hasTerminal = true;
            break;
        }
    }

    if (!hasTerminal) {
        if (_type == LT_FOR) {
            LoopB.CreateStore(LoopB.CreateAdd(LoopB.CreateLoad(CounterV), LoopB.getInt32(-1)), CounterV);
        }

        LoopB.CreateBr(StartBB); // Restart loop (will next exit if current cell value > 0)
    }

    B.SetInsertPoint(EndBB);
}

void LoopExpr::debug_description(int level)
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _exprs.empty()) {
        return;
    }

    char openedBrackets = (_type == LT_FOR) ? TT_BEGIN_FOR : TT_BEGIN_WHILE;
    char closedBrackets = (_type == LT_FOR) ? TT_END_FOR : TT_END_WHILE;

    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "Loop Expression - "
                  << openedBrackets
                  << std::endl;
    }
    else {
        std::cout << "LoopExpr: " << openedBrackets << std::endl;
    }

    for (auto& expr : _exprs) {
        std::cout << std::string(level * 2, ' ');
        expr->debug_description(level+1);

        if (expr->expression_category() == ET_TERMINAL) {
            break;
        }
    }

    std::cout << std::string(level, ' ') << closedBrackets << std::endl;
}

void LoopExpr::ast_code_gen()
{
    if(ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 &&
       _exprs.empty()) {
        return;
    }

    char openedBrackets = (_type == LT_FOR) ? TT_BEGIN_FOR : TT_BEGIN_WHILE;
    char closedBrackets = (_type == LT_FOR) ? TT_END_FOR : TT_END_WHILE;

    std::cout << openedBrackets;
    for (auto& expr : _exprs) {
        expr->ast_code_gen();
        if (expr->expression_category() == ET_TERMINAL) {
            break;
        }
    }

    std::cout << closedBrackets;
}
