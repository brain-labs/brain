/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef EXPR_H
#define EXPR_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "../../utils/ArgsOptions.h"
#include "../general/ASTInfo.h"

#ifndef __cast_capital__
  #define CAST_TO_C_STRING castToCStr
#else
  #define CAST_TO_C_STRING CastToCStr
#endif // __cast_capital__

/**
 * @brief
 */
typedef enum
{
  ET_NOT_IMPORTANT,
  ET_BRANCH,
  ET_TERMINAL
} ExpressionType;

/**
 * @brief Abstract class in which all expressions in Brain implement from.
 */
class Expression
{
public:
    /**
     * @brief
     * @param M
     * @param B
     * @param index
     * @param cells
     */
    virtual void code_gen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells) = 0;
    /**
     * @brief
     * @param level
     */
    virtual void debug_description(int level) = 0;
    /**
     * @brief
     * @param update
     */
    virtual bool update_expression(char update) { return false; }
    /**
     * @brief
     */
    virtual ExpressionType expression_category() { return ET_NOT_IMPORTANT; }
    virtual ~Expression() {};
};

#endif // EXPR_H
