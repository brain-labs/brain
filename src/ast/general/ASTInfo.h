/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef AST_INFO_H
#define AST_INFO_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

/**
 * @brief The abstract syntax tree.
 */
class ASTInfo
{
private:
    /**
     * @brief Private constructor of ASTInfo, denoting that this is a Singleton.
     */
    ASTInfo() {}

    /// Singleton object.
    static ASTInfo *_instance;
    /// An index that points to a Brain's cells position.
    static llvm::GlobalVariable *__brain_index_ptr;
    /// The cells - or memory - of Brain.
    static llvm::GlobalVariable *__brain_cells_ptr;
public:
    ASTInfo(ASTInfo const&) = delete;
    ASTInfo& operator=(ASTInfo const&) = delete;
    /**
     * @brief Returns the instance of ASTInfo class if the member _instance is
     * nullptr, otherwise it creates a new ASTInfo object and returns it.
     * @return A pointer to the ASTInfo instance.
     */
    static ASTInfo* instance();
    /**
     * @brief Generates the IR (Intermediate Representation) code to be
     * executed by llvm.
     * @param M A pointer to the Brain's module.
     * @param B A reference to the Brain's IR builder.
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @returns A pointer to the actual index used by Brain parser.
     */
    llvm::GlobalVariable* get_index_ptr();
    /**
     * @returns  A pointer to the array of cells used as the Brain's memory.
     */
    llvm::GlobalVariable* get_cells_ptr();
    /**
     * @brief Controls if the io.ll module is included within the module which
     * is being interpreted, if the module does not uses any function defined in
     * io.c so it won't include io.ll in their .ll code.
     */
    bool is_using_io_lib;
};

#endif // AST_INFO_H

