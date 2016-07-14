/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef ARITHMETIC_EXPR_H
#define ARITHMETIC_EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <iostream>
#include <string>

#include "Expression.h"

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
class ArithmeticExpression : public Expression
{
protected:
    ArithmeticType _type;
    std::string type_to_string();
public:
    ArithmeticExpression(ArithmeticType type) : _type(type) { }
    /**
     * @brief
     * @param M
     * @param B
     * @param index
     * @param cells
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells);
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
    ~ArithmeticExpression() {};
};

#endif // ARITHMETIC_EXPR_H
