/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef LOOP_EXPR_H
#define LOOP_EXPR_H

#include <vector>
#include "Expr.h"

class LoopExpr : public Expr
{
  protected:
    std::vector<Expr *> _exprs;
  public:
    LoopExpr(std::vector<Expr *> exprs) : _exprs(exprs) { }
    void CodeGen();
};

#endif

