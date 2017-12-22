/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef IF_EXPR_H
#define IF_EXPR_H

#include <vector>
#include <iostream>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "Instr.h"

/**
 * @brief Class that represents the if operator in Brain.
 */
class IfInstr : public Instr
{
protected:
    std::vector<Instr *> _instrs_then;
    std::vector<Instr *> _instrs_else;
public:
    IfInstr(std::vector<Instr *> instrs_then) : _instrs_then(instrs_then) {}
    ~IfInstr() {}

    void set_else(std::vector<Instr *> instrs_else) { _instrs_else = instrs_else; }
    /**
     * @brief Generates the IR (Intermediate Representation) code to be
     * executed by llvm.
     * @param M A pointer to the Brain's module.
     * @param B A reference to the Brain's IR builder.
     * @param BreakBB A pointer to the Brain's basic block.
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                  llvm::BasicBlock *BreakBB);
    /**
     * @brief Prints debug information when Brain's compiler has the active
     * flags: -v | -emit-ast.
     * @param level The width used to display the debug information (to mimic
     * identation).
     */
    void debug_description(int level);
    /**
     * @brief Method for the reverse code generation from the AST. It prints
     * out to the stdout the token itself.
     */
    void ast_code_gen();
    /**
     * @brief Returns the category of the instruction given by the caller.
     */
    InstressionType instruction_category();
};

#endif // IF_EXPR_H

