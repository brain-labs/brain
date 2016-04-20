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

void Parser::parse()
{
   char c = 0;
   while ( (c = getToken()) ) {
     Expr *expr = NULL;
     switch (c)
     {
       case '<':
         expr = new ShiftExpr(-1); break;
       case '>':
         expr = new ShiftExpr(1); break;
       case '+':
         expr = new IncrementExpr(1);
         break;
       case '-':
         expr = new IncrementExpr(-1);
         break;
       case '.':
         expr = new InputExpr();
         break;
       case ',':
         expr = new OutputExpr();
         break;
       case '[':
         break;
       case ']':
         break;
       default: break; // Ignored character
     }

     if (expr) 
     {
       _exprs.push_back(expr);
     }
   }
}


