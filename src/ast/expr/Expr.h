/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
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
 * @brief Tokens brain.
 */
typedef enum 
{
    TT_SHIFT_LEFT  = '<',
    TT_SHIFT_RIGHT = '>',
    TT_INCREMENT   = '+',
    TT_DECREMENT   = '-',
    TT_OUTPUT      = '.',
    TT_INPUT       = ',',
    TT_BEGIN_WHILE = '[',
    TT_END_WHILE   = ']',
    TT_BEGIN_FOR   = '{',
    TT_END_FOR     = '}',
    TT_MUL         = '*',
    TT_DIV         = '/',
    TT_REM         = '%',
    TT_DEBUG       = '#',
    TT_BREAK       = '!',
    TT_IF_THEN     = '?',
    TT_IF_ELSE     = ':',
    TT_IF_END      = ';',
    TT_FLOAT       = '$'
} TokenType;

/**
 * @brief Type of a given expression.
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
class Expr
{
public:
    virtual ~Expr() {}

    /**
     * @brief Virtual method for code generation.
     * @param M The current Module.
     * @param B The current IR Builder.
     * @param BreakBB The outter Basic Block that continues after a loop.
     */
    virtual void code_gen(llvm::Module *M, llvm::IRBuilder<> &B,
                          llvm::BasicBlock *BreakBB) = 0;
    /**
     * @brief Virtual method for the AST's emission.
     * @param level Depth within the AST.
     */
    virtual void debug_description(int level) = 0;
    /**
     * @brief Virtual method for the reverse code generation from the AST. It
     * prints out to the stdout the token itself.
     */
    virtual void ast_code_gen() = 0;
    /**
     * @brief Virtual method for updating the AST exprs.
     * @param update The char whose expression will be updated.
     */
    virtual bool update_expression(char update) { return false; }
    /**
     * @brief Returns the category of the expression given by the caller.
     */
    virtual ExpressionType expression_category() { return ET_NOT_IMPORTANT; }
};

#endif  // EXPR_H
