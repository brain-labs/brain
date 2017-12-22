/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>
#include <string>

#include "Instr.h"

/**
 * @brief The three kinds of arithmetic operations used in Brain: multiplication,
 * division and modulus.
 */
typedef enum
{
  AT_MUL,
  AT_DIV,
  AT_REM
} ArithmeticType;

/**
 * @brief Represents the three arithmetic operations that you can use and abuse
 * in Brain.
 */
class ArithmeticInstr : public Instr
{
protected:
    ArithmeticType _type;
    std::string type_to_string();
public:
    ArithmeticInstr(ArithmeticType type) : _type(type) {}
    ~ArithmeticInstr() {}
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
};

#endif // ARITHMETIC_EXPR_H
