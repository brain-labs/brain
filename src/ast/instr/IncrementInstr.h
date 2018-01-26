/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef INCREMENT_EXPR_H
#define INCREMENT_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>

#include "Instr.h"

/**
 * @brief Class that represent the increment operator in Brain.
 */
class IncrementInstr : public Instr
{
protected:
    int _increment;
public:
    explicit IncrementInstr(int increment) : _increment(increment) { }
    ~IncrementInstr() { }
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
     * @brief Virtual method for updating the AST instrs.
     * @param update The char whose instruction will be updated.
     */
    bool update_instruction(char update);
};

#endif  // INCREMENT_EXPR_H
