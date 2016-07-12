/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
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

static llvm::GlobalVariable *__brain_index_ptr = nullptr;
static llvm::GlobalVariable *__brain_cells_ptr = nullptr;
static bool has_done_then = false;

bool Parser::is_skippable(char c)
{
  return (c != '<' && c != '>' &&
          c != '+' && c != '-' &&
          c != '.' && c != ',' &&
          c != '[' && c != ']' &&
          c != '*' && c != '/' &&
          c != '%' && c != '#' &&
          c != '!' && c != '{' &&
          c != '}' && c != '?' &&
          c != ':' && c != ';');
}

char Parser::get_token()
{
  char c = 0;
  while ( (c = _data[_index++]) && is_skippable(c) ) { }
  return c;
}

void Parser::parse(std::vector<Expression *> &exprs, int level)
{
    char c = 0;
    while ((c = get_token()))  {
	Expression *expr = NULL;
	if (ArgsOptions::instance()->get_optimization() == BO_IS_OPTIMIZING_O1 && !exprs.empty()) {
	    Expression *lastExpr = exprs.back();
	    if (lastExpr->update_expression(c)) {
		continue;
	    }
	}

	switch (c)
	{
	case '<':
	    expr = new ShiftExpression(-1); 
	    break;
	case '>':
	    expr = new ShiftExpression(1); 
	    break;
	case '+':
	    expr = new IncrementExpression(1);
	    break;
	case '-':
	    expr = new IncrementExpression(-1);
	    break;
	case '.':
	    expr = new OutputExpression();
	    break;
	case ',':
	    expr = new InputExpression();
	    break;
	case '[':
	{
	    std::vector<Expression *> loopExpr;
	    parse(loopExpr, level + 1);
	    expr = new LoopExpression(loopExpr, LT_WHILE);
	    break;
	}
	case ']':
	    if (level > 0) {
		return; // exit the recursivity
	    }
	    break; 
	case '{':
	{
	    std::vector<Expression *> loopExpr;
	    parse(loopExpr, level + 1);
	    expr = new LoopExpression(loopExpr, LT_FOR);
	    break;
	}
	case '}':
	    if (level > 0) {
		return; // exit the recursivity
	    }
	    break;
	case '?':
	{
	    std::vector<Expression *> ifExpr;
	    parse(ifExpr, level + 1);
	    expr = new IfExpression(ifExpr);
	    break;
	}
	case ':':
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
		Expression *expr = exprs.back();
		if (expr->expression_category() == ET_BRANCH) {
		    std::vector<Expression *> elseExpr;
		    parse(elseExpr, level + 1);
		    ((IfExpression *)expr)->set_else(elseExpr);
		}
	    }
        
	    has_done_then = false; // reset the flag
	    break;
	case ';':
	    if (level > 0) {
		return;
	    }
	    break;
	case '*':
	    expr = new ArithmeticExpression(AT_MUL);
	    break;
	case '/':
	    expr = new ArithmeticExpression(AT_DIV);
	    break;
	case '%':
	    expr = new ArithmeticExpression(AT_REM);
	    break;
	case '#':
	    expr = new DebugExpression();
	    break;
	case '!':
	    expr = new BreakExpression();
	    break;
	default:
	    // Ignored character
	    break;
	}
    
	if (expr) {
	    exprs.push_back(expr);
	}
    }
}

void Parser::code_gen(llvm::Module *M, llvm::IRBuilder<> &B)
{
    llvm::LLVMContext &C = M->getContext();
  
    if (!__brain_index_ptr) {
	// Create global variable |brainf.index|
	llvm::Type *Ty = llvm::Type::getInt32Ty(C);
	const llvm::APInt Zero = llvm::APInt(32, 0); // int32 0
	llvm::Constant *InitV = llvm::Constant::getIntegerValue(Ty, Zero);
	__brain_index_ptr = new llvm::GlobalVariable(*M, Ty, false /* non-constant */,
                                           llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                           InitV, "brainf.index");
  }
  
    if (!__brain_cells_ptr) {
#define kCellsCount 100
	// Create |brainf.cells|
	llvm::ArrayType *ArrTy = llvm::ArrayType::get(llvm::Type::getInt32Ty(C), kCellsCount);
	std::vector<llvm::Constant *> constants(kCellsCount, B.getInt32(0)); // Create a vector of kCellsCount items equal to 0
	llvm::ArrayRef<llvm::Constant *> Constants = llvm::ArrayRef<llvm::Constant *>(constants);
	llvm::Constant *InitPtr = llvm::ConstantArray::get(ArrTy, Constants);
	__brain_cells_ptr = new llvm::GlobalVariable(*M, ArrTy, false /* non-constant */,
						llvm::GlobalValue::WeakAnyLinkage,
// Keep one copy when linking (weak)
                                           InitPtr, "brainf.cells");
  }

    for (std::vector<Expression *>::iterator it = _exprs.begin();
	 it != _exprs.end(); ++it) {
	(*it)->code_gen(M, B, __brain_index_ptr, __brain_cells_ptr);
    }
}

void Parser::debug_description(int level)
{
    for (std::vector<Expression *>::iterator it = _exprs.begin();
	 it != _exprs.end(); ++it) {
	std::cout << std::string(level * 2, ' ');
	(*it)->debug_description(level+1);
    }
}
