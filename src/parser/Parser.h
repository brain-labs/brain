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

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "../ast/expr/Expr.h"
#include "../utils/ArgsOptions.h"

/**
 * @brief
 */
class Parser
{
protected:
    std::string _data;
    int _index;
    std::vector<Expression *> _exprs;

    /**
     * @brief
     * @param c
     */
    static bool is_skippable(char c);
    /**
     * @brief
     */
    char get_token();
    /**
     * @brief
     * @param exprs
     * @param level
     */
    void parse(std::vector<Expression *> &exprs, int level);
public:
    /**
     * @brief
     * @param s
     */
    Parser(std::string s) : _data(s), _index(0) { parse(_exprs, 0); }
    /**
     * @brief
     * @param M
     * @param B
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @brief
     * @param level
     */
    void debug_description(int level);
};

#endif // PARSER_H 
