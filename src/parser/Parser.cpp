/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "Parser.h"
#include "../ast/expr/ShiftExpr.h"
#include "../ast/expr/IncrementExpr.h"
#include "../ast/expr/InputExpr.h"
#include "../ast/expr/OutputExpr.h"
#include "../ast/expr/LoopExpr.h"
#include "../ast/expr/ArithmeticExpr.h"
#include "../ast/expr/DebugExpr.h"
#include "../ast/expr/BreakExpr.h"
#include "../ast/expr/IfExpr.h"

// Forward declaration of static members
static llvm::GlobalVariable *__brain_index_ptr = nullptr;
static llvm::GlobalVariable *__brain_cells_ptr = nullptr;
static bool has_done_then = false;

void Parser::parse(std::vector<Expr *> &exprs, int level)
{
    char c = 0;
    while ((c = _data[_index++]))  {
        Expr *expr = nullptr;
	if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 && !exprs.empty()) {
            Expr *last_expression = exprs.back();
            	if (last_expression->update_expression(c)) {
  		    continue;
		}
	}

	switch (c)
	{
	case TT_SHIFT_LEFT:
            expr = new ShiftExpr(-1);
	    break;
	case TT_SHIFT_RIGHT:
            expr = new ShiftExpr(1);
	    break;
	case TT_INCREMENT:
            expr = new IncrementExpr(1);
	    break;
	case TT_DECREMENT:
            expr = new IncrementExpr(-1);
	    break;
	case TT_OUTPUT:
            expr = new OutputExpr();
	    break;
	case TT_INPUT:
            expr = new InputExpr();
	    break;
	case TT_BEGIN_WHILE:
	{
            std::vector<Expr *> loop_expression;
	    parse(loop_expression, level + 1);
            expr = new LoopExpr(loop_expression, LT_WHILE);
	    break;
	}
	case TT_END_WHILE:
        {
	    if (level > 0) {
	        // exit the recursivity.
		return;
	    }

	    break;
        } 
	case TT_BEGIN_FOR:
	{
            std::vector<Expr *> loop_expression;
	    parse(loop_expression, level + 1);
            expr = new LoopExpr(loop_expression, LT_FOR);
	    break;
	}
	case TT_END_FOR:
        {
	    if (level > 0) {
	        // exit the recursivity.
		return;
	    }

	    break;
        }
	case TT_IF_THEN:
	{
            std::vector<Expr *> if_expression;
	    parse(if_expression, level + 1);
            expr = new IfExpr(if_expression);
	    break;
	}
	case TT_IF_ELSE:
        {
	    if (!has_done_then) {
	        if (level == 0) {
		    break;
		}

		_index--; // move one step back to read the ':' again
		has_done_then = true;
		return; // return to exit the 'then' recursivity
	    }

	    // do the else
	    if (!exprs.empty()) {
                Expr *expr = exprs.back();
		if (expr->expression_category() == ET_BRANCH) {
                    std::vector<Expr *> else_expression;
		    parse(else_expression, level + 1);
                    ((IfExpr *)expr)->set_else(else_expression);
		}
	    }

	    has_done_then = false; // reset the flag
	    break;
        }
	case TT_IF_END:
        {
	    if (level > 0) {
		return;
	    }

	    break;
        }
	case TT_MUL:
            expr = new ArithmeticExpr(AT_MUL);
	    break;
	case TT_DIV:
            expr = new ArithmeticExpr(AT_DIV);
	    break;
	case TT_REM:
            expr = new ArithmeticExpr(AT_REM);
	    break;
	case TT_DEBUG:
            expr = new DebugExpr();
	    break;
	case TT_BREAK:
            expr = new BreakExpr();
	    break;
	default:
	    // Ignored character
	    continue;
	}

	if (expr) {
	    exprs.push_back(expr);
	}
    }
}

void Parser::code_gen(llvm::Module *M, llvm::IRBuilder<> &B)
{
    llvm::LLVMContext &context = M->getContext();

    if (!__brain_index_ptr) {
        // Create global variable |brainf.index|
        llvm::Type *Ty = llvm::Type::getInt32Ty(context);
        const llvm::APInt Zero = llvm::APInt(32, 0); // int32 0
        llvm::Constant *InitV = llvm::Constant::getIntegerValue(Ty, Zero);
        __brain_index_ptr = new llvm::GlobalVariable(*M, Ty, false, // non-constant
                                                     llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                                     InitV, "brainf.index");
    }

    if (!__brain_cells_ptr) {
        // Create |brainf.cells|
        auto *ArrTy = llvm::ArrayType::get(llvm::Type::getInt32Ty(context),
                                           ArgsOptions::instance()->get_cells_size());
        // Create a vector of _k_cells_size items equal to 0
        std::vector<llvm::Constant *> constants(ArgsOptions::instance()->get_cells_size(),
                                                B.getInt32(0));
        llvm::ArrayRef<llvm::Constant *> Constants = llvm::ArrayRef<llvm::Constant *>(constants);
        llvm::Constant *InitPtr = llvm::ConstantArray::get(ArrTy, Constants);
        __brain_cells_ptr = new llvm::GlobalVariable(*M, ArrTy, false /* non-constant */,
                                                     llvm::GlobalValue::WeakAnyLinkage,
                                                     // Keep one copy when linking (weak)
                                                     InitPtr, "brainf.cells");
    }

    for (auto& expr : _exprs) {
	expr->code_gen(M, B, __brain_index_ptr, __brain_cells_ptr);
    }
}

void Parser::debug_description(int level)
{
    for (auto& expr : _exprs) {
        std::cout << std::string(level * 2, ' ');
        expr->debug_description(level+1);
    }
}

void Parser::ast_code_gen()
{
    for (auto& expr : _exprs) {
        expr->ast_code_gen();
    }
}

