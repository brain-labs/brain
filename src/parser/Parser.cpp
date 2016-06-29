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

static llvm::GlobalVariable *__Brain_IndexPtr = NULL;
static llvm::GlobalVariable *__Brain_CellsPtr = NULL;
static bool hasDoneThen = false;

bool Parser::isSkippable(char c)
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

char Parser::getToken()
{
  char c = 0;
  while ( (c = _data[_index++]) && isSkippable(c) ) { }
  return c;
}

void Parser::parse(std::vector<Expr *> &exprs, int level)
{
   char c = 0;
   while ( (c = getToken()) ) 
   {
     Expr *expr = NULL;
     if (_isOptimizing && !exprs.empty())
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
         parse(loopExpr, level + 1);
         expr = new LoopExpr(loopExpr, LT_WHILE);
         break;
       }
       case ']':
       {
         if (level > 0)
           return; // exit the recursivity
         break; 
       }
       case '{':
       {
         std::vector<Expr *> loopExpr;
         parse(loopExpr, level + 1);
         expr = new LoopExpr(loopExpr, LT_FOR);
         break;
       }
       case '}':
       {
         if (level > 0)
           return; // exit the recursivity
         break;
       }
       case '?':
       {
         std::vector<Expr *> ifExpr;
         parse(ifExpr, level + 1);
         expr = new IfExpr(ifExpr);
         break;
       }
       case ':':
       {
         if (!hasDoneThen)
         {
           if (level == 0)
             break;

           _index--; // move one step back to read the ':' again
           hasDoneThen = true;
           return; // return to exit the 'then' recursivity
         }
        
         if (!exprs.empty()) // do the else
         {
           Expr *expr = exprs.back();
           if (expr->ExprCategory() == ET_BRANCH)
           {
             std::vector<Expr *> elseExpr;
             parse(elseExpr, level + 1);
             ((IfExpr *)expr)->SetElse (elseExpr);
           }
         }

         hasDoneThen = false; // reset the flag       

         break;
       }
       case ';':
       {
         if (level > 0)
           return;
         break;
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
       case '!':
       {
         expr = new BreakExpr();
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
