/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "Parser.h"
#include "ShiftExpr.h"
#include "IncrementExpr.h"
#include "InputExpr.h"
#include "OutputExpr.h"
#include "LoopExpr.h"
#include "ArithmeticExpr.h"
#include "DebugExpr.h"

static llvm::GlobalVariable *__Brain_IndexPtr = NULL;
static llvm::GlobalVariable *__Brain_CellsPtr = NULL;

bool Parser::isSkippable(char c)
{
  return (c != '<' && c != '>' &&
          c != '+' && c != '-' &&
          c != '.' && c != ',' &&
          c != '[' && c != ']' &&
          c != '*' && c != '/' &&
          c != '%' && c != '#');
}

char Parser::getToken()
{
  char c = 0;
  while ( (c = _data[_index++]) && isSkippable(c) ) { }
  return c;
}

void Parser::parse(std::vector<Expr *> &exprs)
{
   char c = 0;
   while ( (c = getToken()) ) 
   {
     Expr *expr = NULL;
     if (_isOptimizing && exprs.size())
     {
       Expr *lastExpr = exprs.back();
       if (lastExpr->UpdateExpr(c))
         continue;
     }

     switch (c)
     {
       case '<':
       {
         expr = new ShiftExpr(-1); 
         break;
       }
       case '>':
       {
         expr = new ShiftExpr(1); 
         break;
       }
       case '+':
       {
         expr = new IncrementExpr(1);
         break;
       }
       case '-':
       {
         expr = new IncrementExpr(-1);
         break;
       }
       case '.':
       {
         expr = new OutputExpr();
         break;
       }
       case ',':
       {
         expr = new InputExpr();
         break;
       }
       case '[':
       {
         std::vector<Expr *> loopExpr;
         parse(loopExpr);
         expr = new LoopExpr(loopExpr);
         break;
       }
       case ']':
       {
         return; // exit the recursivity 
       }
       case '*':
       {
         expr = new ArithmeticExpr(AT_MUL);
         break;
       }
       case '/':
       {
         expr = new ArithmeticExpr(AT_DIV);
         break;
       }
       case '%':
       {
         expr = new ArithmeticExpr(AT_REM);
         break;
       }
       case '#':
       {
         expr = new DebugExpr();
         break;
       }
       default: 
       {
         break; // Ignored character
       }
     }

     if (expr) 
     {
       exprs.push_back(expr);
     }
   }
}

void Parser::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B)
{
  llvm::LLVMContext &C = M->getContext();
  
  if (!__Brain_IndexPtr)
  {
    // Create global variable |brainf.index|
    llvm::Type *Ty = llvm::Type::getInt32Ty(C);
    const llvm::APInt Zero = llvm::APInt(32, 0); // int32 0
    llvm::Constant *InitV = llvm::Constant::getIntegerValue(Ty, Zero);
    __Brain_IndexPtr = new llvm::GlobalVariable(*M, Ty, false /* non-constant */,
                                           llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                           InitV, "brainf.index");
  }
  
  if (!__Brain_CellsPtr)
  {
    #define kCellsCount 100
    // Create |brainf.cells|
    llvm::ArrayType *ArrTy = llvm::ArrayType::get(llvm::Type::getInt32Ty(C), kCellsCount);
    std::vector<llvm::Constant *> constants(kCellsCount, B.getInt32(0)); // Create a vector of kCellsCount items equal to 0
    llvm::ArrayRef<llvm::Constant *> Constants = llvm::ArrayRef<llvm::Constant *>(constants);
    llvm::Constant *InitPtr = llvm::ConstantArray::get(ArrTy, Constants);
    __Brain_CellsPtr = new llvm::GlobalVariable(*M, ArrTy, false /* non-constant */,
                                           llvm::GlobalValue::WeakAnyLinkage, // Keep one copy when linking (weak)
                                           InitPtr, "brainf.cells");
  }

  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it) 
  {
    (*it)->CodeGen(M, B, __Brain_IndexPtr, __Brain_CellsPtr);
  }
}

void Parser::DebugDescription(int level)
{
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it) 
  {
    std::cout << std::string(level * 2, ' ');
    (*it)->DebugDescription(level+1);
  }
}
