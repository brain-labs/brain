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

bool Parser::isSkippable(char c)
{
  return (c != '<' && c != '>' &&
          c != '+' && c != '-' &&
          c != '.' && c != ',' &&
          c != '[' && c != ']');
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
   while ( (c = getToken()) ) {
     Expr *expr = NULL;
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
         expr = new InputExpr();
         break;
       }
       case ',':
       {
         expr = new OutputExpr();
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
  for (std::vector<Expr *>::iterator it = _exprs.begin(); it != _exprs.end(); ++it) 
  {
    (*it)->CodeGen(M, B);
  }
}

void Parser::DebugDescription(int level)
{
}
