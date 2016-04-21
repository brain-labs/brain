/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

#include "Expr.h"

class Parser
{
  protected:
    std::string _data;
    int _index;
    std::vector<Expr *> _exprs;
  
    static bool isSkippable(char c);
    char getToken();
    void parse(std::vector<Expr *> &exprs);
  public:
    Parser(std::string s) : _data(s), _index(0) { parse(_exprs); }
    void CodeGen(llvm::Module *M, llvm::IRBuilder<> &B);
    void DebugDescription(int level);
};

#endif 
