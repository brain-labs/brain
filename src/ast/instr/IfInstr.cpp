/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "IfInstr.h"
#include "../../utils/ArgsOptions.h"
#include "../general/ASTInfo.h"

void IfInstr::code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
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
                                       // Cast to int 8*, 16*, 32* or 64*
                                       ASTInfo::instance()->get_cell_type(C)->getPointerTo()),
                                       IdxV);
    llvm::Value *NEZeroCond = B.CreateICmpNE(B.CreateLoad(CellPtr),
                                             // is cell signed int not equal
                                             // to zero?
                                             B.getIntN(ArgsOptions::instance()->get_cell_bitsize(), 0));

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
        !_instrs_else.empty()) {
        ElseBB = llvm::BasicBlock::Create(C, "ElseBody", F);
        B.CreateCondBr(NEZeroCond, ThenBB, ElseBB);
    }
    else {
        B.CreateCondBr(NEZeroCond, ThenBB, ContBB);
    }

    B.SetInsertPoint(ThenBB);
    llvm::IRBuilder<> ThenB(ThenBB);

    bool hasTerminal = false;
    for (auto& instr : _instrs_then) {
        instr->code_gen(M, ThenB, BreakBB);
        if (instr->instruction_category() == ET_TERMINAL) {
            hasTerminal = true;
            break;
        }
    }

    if (!hasTerminal) {
        ThenB.CreateBr(ContBB); // uncoditional jump
    }

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_instrs_else.empty()) {
        B.SetInsertPoint(ElseBB);
        llvm::IRBuilder<> ElseB(ElseBB);
        hasTerminal = false;
        for (auto& instr : _instrs_else) {
            instr->code_gen(M, ElseB, BreakBB);
            if (instr->instruction_category() == ET_TERMINAL) {
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

void IfInstr::debug_description(int level)
{
    if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
        std::cout << "If Instruction - THEN - if cell "
                  << " != 0 ["
                  << std::endl;
    }
    else {
        std::cout << "IfInstr (THEN) [" << std::endl;
    }

    for (auto& instr : _instrs_then) {
        std::cout << std::string(level * 2, ' ');
        instr->debug_description(level+1);
        if (instr->instruction_category() == ET_TERMINAL) {
            break;
        }
    }

    std::cout << std::string(level, ' ') << "]" << std::endl;

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_instrs_else.empty()) {
        if (ArgsOptions::instance()->has_option(BO_IS_VERBOSE)) {
            std::cout << std::string(level, ' ')
                      << "If Instruction - ELSE - ["
                      << std::endl;
        }
        else {
            std::cout << std::string(level, ' ')
                      << "IfInstr (ELSE) ["
                      << std::endl;
        }

        for (auto& instr : _instrs_else) {
            std::cout << std::string(level * 2, ' ');
            instr->debug_description(level+1);
            if (instr->instruction_category() == ET_TERMINAL) {
                break;
            }
        }

        std::cout << std::string(level, ' ') << "]" << std::endl;
    }
}

void IfInstr::ast_code_gen()
{
    std::cout << static_cast<char>(TT_IF_THEN);
    for (auto& instr : _instrs_then) {
        instr->ast_code_gen();
        if (instr->instruction_category() == ET_TERMINAL) {
            break;
        }
    }

    if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O0 ||
            !_instrs_else.empty()) {
        std::cout << static_cast<char>(TT_IF_ELSE);
        for (auto& instr : _instrs_else) {
            instr->ast_code_gen();
            if (instr->instruction_category() == ET_TERMINAL) {
                break;
            }
        }
    }

    std::cout << (char)TT_IF_END;
}

InstructionType IfInstr::instruction_category()
{
    return ET_BRANCH;
}

