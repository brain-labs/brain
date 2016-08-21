/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef PARSER_H
#define PARSER_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include <string>
#include <vector>

#include "../ast/general/ASTInfo.h"
#include "../ast/expr/Expr.h"
#include "../utils/ArgsOptions.h"

/**
 * @brief The parser of the Brain language, it interpretes *.b, *.br or
 * *.brain files.
 */
class Parser
{
protected:
    /// The content of the source file passed to Brain.
    std::string _data;
    /// Variable that holds the current index read by the parser.
    int _index;
    /**
     * Store pointers of expressions to later call code_gen on each one of
     * them.
     */
    std::vector<Expr *> _exprs;

    /**
     * @brief It parses the Brain code.
     * @param exprs The vector of expressions read by the constructor
     * @param level
     */
    void parse(std::vector<Expr *> &exprs, int level);
public:
    /**
     * @brief Calls parse to <i>create</i> all expressions found in the source
     * code.
     * @param source The source file as a string of characters.
     * interpreter
     */
    explicit Parser(std::string source) :
        _data(source), _index(0) { parse(_exprs, 0); }
    /**
     * @brief Generates the IR (Intermediate Representation) code to be
     * executed by llvm.
     * @param M A pointer to the Brain's module.
     * @param B A reference to the Brain's IR builder.
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @brief Prints debug information when Brain's compiler has the active
     * flags: -v | -emit-ast.
     * @param level The width used to display the debug information (to mimic
     * identation).
     */
    void debug_description(int level);
    /**
     * @brief Method for the reverse code generation from the AST. It prints
     * out to the stdout the token itself.
     */
    void ast_code_gen();
};

#endif  // PARSER_H
